#pragma once

#include <glm/glm.hpp>

namespace Phoenix {
	// 2D camera
	class OrthoCamera {
	public:
		OrthoCamera(float left, float right, float bottom, float top); // 1, for near -1 for far provide
		~OrthoCamera();

		const glm::vec3& GetPosition() const { return position; }

		void SetPosition(const glm::vec3& position) { this->position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { this->rotation = rotation; RecalculateViewMatrix(); }

		float GetRotation() const { return rotation; }

		inline const glm::mat4 GetViewMatrix() const { return viewMatrix; }
		inline const glm::mat4 GetProjectionMatrix() const { return viewMatrix; }
		inline const glm::mat4 GetVPMatrix() const { return projMatrix * viewMatrix; }
		// Add vertices = projMatrix x viewMatrix x modelMatrix x vertexPos -- glm order
		// directx is vertexPos x modelx viewx proj
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 viewMatrix;
		glm::mat4 projMatrix; // FOV, AspectRatio

		glm::vec3 position;
		float rotation = 0.0f;
		
	};

}