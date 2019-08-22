#pragma once

namespace Phoenix {

	enum class RendererAPI {
		None = 0, OpenGL = 1, DirectX12 = 2
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
	private:

		static RendererAPI rendererAPI;
	};

}