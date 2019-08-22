#pragma once

#include "Phoenix/Renderer/Buffer.h"

#include <stdint.h>

namespace Phoenix {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout; };
		virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; };
	private:
		uint32_t rendererID;
		BufferLayout layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return count; }

	private:
		uint32_t rendererID;
		uint32_t count;
	};

}