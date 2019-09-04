#include "pcheaders.h"

#include "Application.h"

#include "Phoenix/Renderer/Renderer.h"

namespace Phoenix {

#define BIND_FN_TO_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	// 'instance' is static so it will initially be set to nullptr
	Application* Application::instance = nullptr;

	//	Creates an instance of application, a Window object for rendering, and an ImGuiLayer that is pushed onto the LayerStack.
	Application::Application()
		: camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		PHX_CORE_ASSERT(instance, "Application exists");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FN_TO_EVENT(OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);

		vertexArray.reset(VertexArray::Create());

		// Anti Aliasing
		//glEnable(GL_POLYGON_SMOOTH);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
		
		// Triangle render
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,	 0.5f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,	 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f,	 1.0f, 0.0f, 1.0f, 1.0f,
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }
		};
		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->AddIndexBuffer(indexBuffer);

		// Square render
		squareVertexArray.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout layout2 = {
			{ ShaderDataType::Float3, "position" },
		};
		squareVertexBuffer->SetLayout(layout2);
		squareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->AddIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;
			layout(location = 1) in vec4 color;
			
			uniform mat4 viewProjection;

			out vec3 vPosition;
			out vec4 vColor;
			
			void main() {
				vPosition = position;
				vColor = color;
				gl_Position = viewProjection * vec4(position, 1.0);
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

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 position;

			uniform mat4 viewProjection;

			out vec3 vPosition;
			
			void main() {
				vPosition = position;
				gl_Position = viewProjection * vec4(position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";
		
		shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		shader2.reset(Shader::Create(vertexSrc2, fragmentSrc2));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			camera.SetPosition({ 0.2f, 0.5f, 0.0f });
			camera.SetRotation(45.0f);

			Renderer::BeginScene(camera);

			Renderer::Submit(squareVertexArray, shader2);

			Renderer::Submit(vertexArray, shader);

			Renderer::EndScene();

			// Renderer::Flush(); Multi thread

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