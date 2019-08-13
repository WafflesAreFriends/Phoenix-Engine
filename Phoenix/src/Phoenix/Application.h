#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

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

		unsigned int vertexArray, vertexBuffer, indexBuffer;

		bool running = true;
	};

	// Client-defined function that takes an Application created by the client and runs it through the engine.
	Application* CreateApplication();

}