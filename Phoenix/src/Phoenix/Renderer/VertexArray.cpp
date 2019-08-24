#include "pcheaders.h"
#include "VertexArray.h"


#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Phoenix {

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			PHX_CORE_ASSERT(false, "return nullptr");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		PHX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}