#include "pcheaders.h"
#include "VertexArray.h"


#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Phoenix {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetGraphicsAPI()) {
		case RendererAPI::GraphicsAPI::None:
			PHX_CORE_ASSERT(false, "No API Selected");
			return nullptr;
		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		PHX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}