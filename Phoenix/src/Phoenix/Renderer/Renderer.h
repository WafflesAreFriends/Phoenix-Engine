#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

#include "OrthoCamera.h"
#include "Shader.h"

namespace Phoenix {

	class Renderer {
	public:
		static void BeginScene(OrthoCamera& camera); // Scene params
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::GraphicsAPI GetGraphicsAPI() { return RendererAPI::GetGraphicsAPI(); }
	private:
		struct SceneData {
			glm::mat4 vpMatrix;
		};

		static SceneData* sceneData;
	};

}