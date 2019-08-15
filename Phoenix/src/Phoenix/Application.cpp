#include "pcheaders.h"

#include "Application.h"

#include <glad/glad.h>

namespace Phoenix {

#define BIND_FN_TO_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	// 'instance' is static so it will initially be set to nullptr
	Application* Application::instance = nullptr;

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

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3]{ 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			out vec3 vPosition;
			
			void main() {
				vPosition = position;
				gl_Position = vec4(position + 0.5, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 vPosition;

			void main() {
				color = vec4(vPosition * 0.5 + 0.5, 1.0);
			}
		)";
		
		shader.reset(new OpenGLShader(vertexSrc, fragmentSrc));
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
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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