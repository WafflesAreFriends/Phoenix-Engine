#pragma once

#include "Phoenix/Renderer/VertexArray.h"

namespace Phoenix {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; // Intrusive reference counting system
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; };
		virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const override { return indexBuffers; };
	private:
		uint32_t rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::vector<std::shared_ptr<IndexBuffer>> indexBuffers;
	};

}