#include "pcheaders.h"

#include "Application.h"

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
	}

	Application::~Application() {
		delete instance;
	}

	////
	////	- Updates all layers
	////	- Updates all ImGuiLayers and renders ImGui to them.
	////		NOTE:Because ImGui is an immediate mode API, must be called each time
	////		within the render loop. If changed to retained mode API, take out of loop.
	////	- Updates window
	////

	void Application::Run() {
		while (running) {
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