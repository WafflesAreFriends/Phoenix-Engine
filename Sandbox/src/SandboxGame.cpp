#include "pcheaders.h"
#include <Phoenix.h>

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {}

	void OnUpdate() override {
		
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