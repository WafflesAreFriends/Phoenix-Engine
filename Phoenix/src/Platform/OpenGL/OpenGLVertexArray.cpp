#include "pcheaders.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Phoenix {

	static GLenum SDTToOpenGLType(ShaderDataType type) {
		switch (type) {
		case Phoenix::ShaderDataType::Float:  return GL_FLOAT;
		case Phoenix::ShaderDataType::Float2: return GL_FLOAT;
		case Phoenix::ShaderDataType::Float3: return GL_FLOAT;
		case Phoenix::ShaderDataType::Float4: return GL_FLOAT;
		case Phoenix::ShaderDataType::Mat3:   return GL_FLOAT;
		case Phoenix::ShaderDataType::Mat4:   return GL_FLOAT;
		case Phoenix::ShaderDataType::Int:    return GL_INT;
		case Phoenix::ShaderDataType::Int2:   return GL_INT;
		case Phoenix::ShaderDataType::Int3:   return GL_INT;
		case Phoenix::ShaderDataType::Int4:   return GL_INT;
		case Phoenix::ShaderDataType::Bool:   return GL_BOOL;
		}
		PHX_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		PHX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements.size(), "Vertex buffer has no layout!");

		uint32_t index = 0;
		for (const BufferElement& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				SDTToOpenGLType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.offset);
			index++;
		}
		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(rendererID);
		indexBuffer->Bind();

		indexBuffers.push_back(indexBuffer);
	}

}