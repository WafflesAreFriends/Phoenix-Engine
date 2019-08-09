#pragma once
// Static polling

#include "Core.h"

namespace Phoenix {

	class PHX_API Input {
	public:
		inline static bool IsKeyPressed(int keyCode) { return instance->IsKeyPressedImpl(keyCode); }

		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePos() { return instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0; // Per platform implementation

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static Input* instance;


	};

}