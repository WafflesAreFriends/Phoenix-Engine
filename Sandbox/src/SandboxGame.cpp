#include "pcheaders.h"
#include <Phoenix.h>

#include "imgui/imgui.h"

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {}

	//-- Update per frame --//
	void OnUpdate() override {
		
	}

	//-- Implement ImGui here --//
	void OnImGuiRender() override {
		bool show = true;
		ImGui::Begin("Output");
		ImGui::Text("Phoenix Engine Output");
		ImGui::End();
	}

	//-- Implement event action for this layer --//
	void OnEvent(Phoenix::Event& event) override {
		if (event.GetEventType() == Phoenix::EventType::KeyPressed) {
			Phoenix::KeyPressedEvent& e = (Phoenix::KeyPressedEvent&) event;
			if (e.GetKeyCode() == PHX_KEY_TAB) {
				PHX_INFO("Tab has been pressed!");
			}
		}
	}
};

class Sandbox : public Phoenix::Application {
public:
	// Pushing layers and overlays into Sandbox
	Sandbox() {
		PushLayer(new ExLayer());
	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox();
}