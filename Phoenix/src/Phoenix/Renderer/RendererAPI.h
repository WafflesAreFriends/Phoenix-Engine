#pragma once

#include "VertexArray.h"
#include <glm/glm.hpp>

namespace Phoenix {

	class RendererAPI {
	public:
		enum class GraphicsAPI {
			None = 0, OpenGL = 1, DirectX12 = 2
		};

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static GraphicsAPI GetGraphicsAPI() { return gAPI; }
	private:
		static GraphicsAPI gAPI;
	};

}