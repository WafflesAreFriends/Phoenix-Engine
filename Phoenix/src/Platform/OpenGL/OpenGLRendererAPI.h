#pragma once

#include "Phoenix/Renderer/RendererAPI.h"

namespace Phoenix {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void EnableAntiAliasing() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;


	};

}