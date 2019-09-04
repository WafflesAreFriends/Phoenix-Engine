#include "pcheaders.h"
#include "Renderer.h"

namespace Phoenix {

	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthoCamera& camera) {
		sceneData->vpMatrix = camera.GetVPMatrix();
	}

	void Renderer::EndScene() {
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
		shader->Bind();
		shader->UploadUniformMat4("viewProjection", sceneData->vpMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);

	}

}