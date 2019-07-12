#include "pcheaders.h"
#include "Application.h"

#include "Phoenix/Log.h"

#include <GLFW/glfw3.h>

using namespace std;

namespace Phoenix {

#define BIND_FN_TO_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FN_TO_EVENT(OnEvent));
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& event) {
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_FN_TO_EVENT(OnWindowClose));

		PHX_CORE_TRACE("{0}", event);
	}

	void Application::Run() {
		while (running) {
			glClearColor(0, 0.5, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		running = false;
		return true;
	}

}