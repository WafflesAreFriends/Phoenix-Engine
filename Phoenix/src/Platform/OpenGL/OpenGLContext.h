#pragma once

#include "Phoenix/Renderer/GraphicsContext.h"

#include "glfw/glfw3.h"

namespace Phoenix {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};

}