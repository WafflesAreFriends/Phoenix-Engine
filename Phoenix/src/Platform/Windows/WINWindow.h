#pragma once

#include "Phoenix/Window.h"
#include "Phoenix/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Phoenix {

	class WINWindow : public Window {
	public:
		WINWindow(const WindowProps& props);
		virtual ~WINWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;
		GraphicsContext* context;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vsync;

			EventCallbackFn eventCallback;
		};

		WindowData data;

	};

}