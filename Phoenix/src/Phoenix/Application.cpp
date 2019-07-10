#include "Application.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Log.h"


#include <iostream>

using namespace std;

namespace Phoenix {

	Application::Application() {
	
	}


	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		PHX_TRACE(e);
	
		while (true);
	}
}