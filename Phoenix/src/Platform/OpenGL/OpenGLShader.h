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
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& values) override;
	private:
		uint32_t rendererID;
	};

}