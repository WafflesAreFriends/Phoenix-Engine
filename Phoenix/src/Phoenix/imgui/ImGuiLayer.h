#pragma once

#include "Phoenix/Layer.h"
// Professional game engine, have own UI

namespace Phoenix {

	class PHX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float time = 0.0f;
	};

}