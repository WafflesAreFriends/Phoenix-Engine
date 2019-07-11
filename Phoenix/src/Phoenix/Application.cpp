#include "pcheaders.h"
#include "Application.h"

#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Log.h"

#include <GLFW/glfw3.h>

using namespace std;

namespace Phoenix {

	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (running) {
			glClearColor(0, 0.5, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}
}