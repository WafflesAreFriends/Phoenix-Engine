#pragma once

#include "Phoenix/Core.h"
#include "Phoenix/Events/Event.h"

namespace Phoenix {

	class PHX_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		// Debug
		inline const std::string& GetName() const { return debugName; }
	protected:
		bool enabled = true;
		std::string debugName;
	};

}