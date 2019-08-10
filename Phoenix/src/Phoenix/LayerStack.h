#pragma once

#include "Phoenix/Core.h"
#include "Layer.h"

#include <vector>

namespace Phoenix {

	class PHX_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return stack.begin(); }
		std::vector<Layer*>::iterator end() { return stack.end(); }
	private:
		std::vector<Layer*> stack; // First half of stack is layers, second half are overlays
		unsigned int stackInsertIndex = 0;

	};

}