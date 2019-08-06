#include "pcheaders.h"
#include "WINWindow.h"

#include "Phoenix/Events/Event.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Phoenix {

	static bool glfwInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		PHX_CORE_ERROR("GLFW Error {0}): {1}", error, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			glfwInitialized = true;
		}
		window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		gladLoadGL();
		PHX_CORE_ASSERT(status, "Failed to initialize GLAD!")

		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		// Have better list of call backs

		// set GLFW callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.eventCallback(event);
		});
		// Convert keycodes for not using glfw
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});
		
		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent event((float) xOffset, (float) yOffset);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double posX, double posY) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)posX, (float)posY);
			data.eventCallback(event);
		});
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