#include "pcheaders.h"

#include <unordered_map>

#include <string>

#include "Application.h"

#include <glad/glad.h>

namespace Phoenix {

#define BIND_FN_TO_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	// 'instance' is static so it will initially be set to nullptr
	Application* Application::instance = nullptr;

	static GLenum SDTToOpenGLType(ShaderDataType type) {
		switch (type) {
		case Phoenix::ShaderDataType::Float:  return GL_FLOAT;
		case Phoenix::ShaderDataType::Float2: return GL_FLOAT;
		case Phoenix::ShaderDataType::Float3: return GL_FLOAT;
		case Phoenix::ShaderDataType::Float4: return GL_FLOAT;
		case Phoenix::ShaderDataType::Mat3:   return GL_FLOAT;
		case Phoenix::ShaderDataType::Mat4:   return GL_FLOAT;
		case Phoenix::ShaderDataType::Int:    return GL_INT;
		case Phoenix::ShaderDataType::Int2:   return GL_INT;
		case Phoenix::ShaderDataType::Int3:   return GL_INT;
		case Phoenix::ShaderDataType::Int4:   return GL_INT;
		case Phoenix::ShaderDataType::Bool:   return GL_BOOL;
		}
		PHX_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	//	Creates an instance of application, a Window object for rendering, and an ImGuiLayer that is pushed onto the LayerStack.
	Application::Application() {
		PHX_CORE_ASSERT(instance, "Application exists");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FN_TO_EVENT(OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
	
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "position" },
				{ ShaderDataType::Float4, "color" }
			};

			vertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const BufferElement& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				SDTToOpenGLType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.offset); 
			index++; 
		} 
		unsigned int indices[3] = { 0, 1, 2 };

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main() {
				vPosition = position;
				vColor = color;
				gl_Position = vec4(position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			in vec4 vColor;

			void main() {
				color = vec4(vPosition * 0.5 + 0.5, 1.0);
				color = vColor;
			}
		)";
		
		shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() {
		delete instance;
	}

	/*
		- Updates all layers
		- Updates all ImGuiLayers and renders ImGui to them.
			NOTE:Because ImGui is an immediate mode API, must be called each time
			within the render loop. If changed to retained mode API, take out of loop.
		- Updates window
	*/
	void Application::Run() {
		while (running) {
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->Bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			// Will be executed in future render thread for multi threading
			imGuiLayer->BeginRender();
			for (Layer* layer : layerStack) {
				layer->OnImGuiRender();
			}
			imGuiLayer->EndRender();

			window->OnUpdate();
		}
	}

	// Dispatches a WindowCloseEvent with OnWindowClose and tells the layers in the LayerStack that the window has been closed.
	void Application::OnEvent(Event& event) {
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_FN_TO_EVENT(OnWindowClose));

		for (auto i = layerStack.end(); i != layerStack.begin();) {
			(*--i)->OnEvent(event);
			if (event.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		layerStack.PushOverlay(overlay);
	}

	// Tells the application to stop running and returns true for Event handler
	bool Application::OnWindowClose(WindowCloseEvent& event) {
		running = false;
		return true;
	}

}