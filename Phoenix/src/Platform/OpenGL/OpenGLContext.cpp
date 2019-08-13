#include "pcheaders.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Phoenix {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
		: windowHandle(windowHandle) {
		PHX_CORE_ASSERT(windowHandle, "Window handle null")
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		gladLoadGL();
		PHX_CORE_ASSERT(status, "Failed to initialize GLAD!")
		PHX_CORE_INFO("OpenGL vendor: {0}", glGetString(GL_VENDOR));
		PHX_CORE_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(windowHandle);
	}

}