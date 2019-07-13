#include "pcheaders.h"
#include "LayerStack.h"

namespace Phoenix {

	LayerStack::LayerStack() {
		stackItr = stack.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : stack) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		stack.emplace(stackItr, layer);
	}
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(stack.begin(), stack.end(), layer);
		if (it != stack.end()) {
			stack.erase(it);
			stackItr--;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		stack.push_back(overlay);
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(stack.begin(), stack.end(), overlay);
		if (it != stack.end()) {
			stack.erase(it);
		}
	}
}