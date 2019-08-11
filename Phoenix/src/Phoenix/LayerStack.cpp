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
		layer->OnAttach();
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
		overlay->OnAttach();
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(stack.begin(), stack.end(), overlay);
		if (it != stack.end()) {
			stack.erase(it);
		}
	}
}