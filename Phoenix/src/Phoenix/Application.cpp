#include "pcheaders.h"
#include "Application.h"

#include "Phoenix/Log.h"

#include <glad/glad.h>

#include "Input.h"

using namespace std;

namespace Phoenix {

#define BIND_FN_TO_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::instance = nullptr;

	Application::Application() {
		PHX_CORE_ASSERT(instance, "Application exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_FN_TO_EVENT(OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowCloseEvent>(BIND_FN_TO_EVENT(OnWindowClose));

	//	PHX_CORE_TRACE("{0}", event);

		for (auto i = layerStack.end(); i != layerStack.begin();) {
			(*--i)->OnEvent(event);
			if (event.IsHandled())
				break;
		}
	}

	void Application::Run() {
		while (running) {
			glClearColor(0, 0.5, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			// Will be executed in future render thread
			imGuiLayer->BeginRender();
			for (Layer* layer : layerStack) {
				layer->OnImGuiRender();
			}
			imGuiLayer->EndRender();

			window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		running = false;
		return true;
	}

}