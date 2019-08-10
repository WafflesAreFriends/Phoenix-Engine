#include "pcheaders.h"
#include <Phoenix.h>

#include "imgui/imgui.h"

class ExLayer : public Phoenix::Layer {
public:
	ExLayer() : Layer("Example") {

	}

	void OnUpdate() override {
		if (Phoenix::Input::IsKeyPressed(PHX_KEY_1))
			PHX_INFO("1 Key pressed!");
	}

	virtual void OnImGuiRender() override {
		bool show = true;
		ImGui::Begin("Test");
		ImGui::Checkbox("Hey", &show);
		ImGui::End();
	}

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
	
	Sandbox() {
		PushLayer(new ExLayer());
	}

	~Sandbox() {

	}

};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox();
}