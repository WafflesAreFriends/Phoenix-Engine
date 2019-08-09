#include "pcheaders.h"
#include <Phoenix.h>

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {}

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