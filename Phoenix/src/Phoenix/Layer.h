#pragma once

#include "Core.h"
#include "Events/Event.h"

#include "Timestep.h"

namespace Phoenix {

	class PHX_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() {};

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}

		// For debugging
		inline const std::string& GetName() const { return debugName; }
	protected:
		std::string debugName;
		bool enabled = true;
	};

}