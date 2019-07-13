#pragma once

#include "Core.h"

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Phoenix {

	class PHX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;
	};

	// Defined in client
	Application* CreateApplication();

}