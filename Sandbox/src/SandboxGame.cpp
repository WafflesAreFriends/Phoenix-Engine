#include "pcheaders.h"
#include <Phoenix.h>
#include "glm/glm.hpp"

// Math lib
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const & Rotate) {
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {
		auto cam = camera(5.0f, { 0.5f, 0.5f });
	}

	void OnUpdate() override {
		if (Phoenix::Input::IsKeyPressed(PHX_KEY_1))
			PHX_INFO("1 Key pressed!");
	}

	void OnEvent(Phoenix::Event& event) override {
		
	}
};

class Sandbox : public Phoenix::Application {

public:
	
	Sandbox() {
		PushLayer(new ExLayer());
		PushOverlay(new Phoenix::ImGuiLayer());
	}

	~Sandbox() {

	}

};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox();
}