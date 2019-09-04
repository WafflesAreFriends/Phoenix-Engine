#include "pcheaders.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Phoenix {

	Shader* Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc) {
		switch (Renderer::GetGraphicsAPI()) {
		case RendererAPI::GraphicsAPI::None:
			PHX_CORE_ASSERT(false, "No API Selected");
			return nullptr;
		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		PHX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}