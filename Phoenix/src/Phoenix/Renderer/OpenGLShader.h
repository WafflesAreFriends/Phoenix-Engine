#pragma once

#include <string>

namespace Phoenix {

	class OpenGLShader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t rendererID;
	};

}