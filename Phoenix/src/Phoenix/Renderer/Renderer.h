#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Phoenix {

	class Renderer {
	public:
		static void BeginScene(); // Scene params
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::GraphicsAPI GetGraphicsAPI() { return RendererAPI::GetGraphicsAPI(); }
	};

}