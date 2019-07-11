#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Phoenix {

	class PHX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// Defined in client
	Application* CreateApplication();

}