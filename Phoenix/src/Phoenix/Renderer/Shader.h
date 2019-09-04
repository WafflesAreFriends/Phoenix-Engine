#pragma once

#include <string> // std::string
#include <glm/glm.hpp>

namespace Phoenix {

	class Shader {
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& projMatName, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}