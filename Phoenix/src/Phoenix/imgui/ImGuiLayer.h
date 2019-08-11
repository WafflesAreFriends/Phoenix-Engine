#pragma once

#include "Phoenix/Layer.h"

#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"
// Professional game engine, have own UI

namespace Phoenix {

	class PHX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void BeginRender();
		void EndRender();
	private:
		float time = 0.0f;
	};

}