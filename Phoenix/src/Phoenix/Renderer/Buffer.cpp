#include "pcheaders.h"
#include "Buffer.h"

#include "Renderer.h"
#include "OrthoCamera.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#if PHX_PLATFORM_WINDOWS
//#include "Platform/Direct3d/Direct3dBuffer.h"
#endif

namespace Phoenix {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetGraphicsAPI()) {
		case RendererAPI::GraphicsAPI::None:
			PHX_CORE_ASSERT(false, "No API Selected");
			return nullptr;
		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
		PHX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetGraphicsAPI()) {
		case RendererAPI::GraphicsAPI::None:
			PHX_CORE_ASSERT(false, "No API Selected");
			return nullptr;
		case RendererAPI::GraphicsAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, sizeof(indices)*count);
		}
		PHX_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
