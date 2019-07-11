#include "pcheaders.h"
#include "WINWindow.h"

namespace Phoenix {

	static bool glfwInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WINWindow(props);
	}

	WINWindow::WINWindow(const WindowProps& props) { // Store in unique pointer
		Init(props);
	}


	WINWindow::~WINWindow() {
		Shutdown();
	}

	void WINWindow::Init(const WindowProps& props) {
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		PHX_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!glfwInitialized) {
			int success = glfwInit();
			PHX_CORE_ASSERT(success, "Could not initialize GLFW")

			glfwInitialized = true;
		}
		window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	void WINWindow::Shutdown() {
		glfwDestroyWindow(window);
	}

	void WINWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WINWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		data.vsync = enabled;
	}
	bool WINWindow::IsVSync() const {
		return data.vsync;
	}

}