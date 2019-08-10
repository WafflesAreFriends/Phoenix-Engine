#include "pcheaders.h"
#include "LayerStack.h"

namespace Phoenix {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : stack) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		stack.emplace(stack.begin() + stackInsertIndex, layer);
		stackInsertIndex++;
	}
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(stack.begin(), stack.end(), layer);
		if (it != stack.end()) {
			stack.erase(it);
			stackInsertIndex--;
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