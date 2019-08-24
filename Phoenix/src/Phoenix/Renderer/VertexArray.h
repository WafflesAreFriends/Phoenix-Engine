#pragma once

#include "Phoenix/Renderer/Buffer.h"

namespace Phoenix {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; // Intrusive reference counting system
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const = 0;

		static VertexArray* Create();
	};

}