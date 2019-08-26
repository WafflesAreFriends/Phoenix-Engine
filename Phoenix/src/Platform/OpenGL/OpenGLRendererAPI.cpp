#include "pcheaders.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Phoenix {
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 & color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Flags to clear in future
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()[0]->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}