#pragma once

#include "Phoenix/Renderer/Shader.h"

namespace Phoenix {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void UploadUniformMat4(const std::string& projMatName, const glm::mat4& matrix) override;
	private:
		uint32_t rendererID;
	};

}