#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Shader.h"

#include "Phoenix/Renderer/OrthoCamera.h"

namespace Phoenix {

	class PHX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& GetInstance() { return *instance; }
		inline Window& GetWindow() { return *window; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		static Application* instance;

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;

		std::shared_ptr<VertexArray> triangleVertexArray;
		std::shared_ptr<VertexArray> squareVertexArray;

		std::shared_ptr<Shader> triangleShader;
		std::shared_ptr<Shader> squareShader;

		OrthoCamera camera;

		bool running = true;
	};

	// Client-defined function that takes an Application created by the client and runs it through the engine.
	Application* CreateApplication();

}