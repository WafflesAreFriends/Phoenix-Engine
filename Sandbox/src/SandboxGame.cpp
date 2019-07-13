#include "pcheaders.h"
#include <Phoenix.h>

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {}

	void OnUpdate() override {
		PHX_INFO("ExampleLayer::Update");
	}

	void OnEvent(Phoenix::Event& event) override {
		PHX_TRACE("{0}", event);
	}
};

class Sandbox : public Phoenix::Application {

public:
	
	Sandbox() {
		PushLayer(new ExLayer());
	}

	~Sandbox() {

	}

};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox();
}