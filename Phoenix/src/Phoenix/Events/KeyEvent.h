#pragma once

#include "Event.h"

namespace Phoenix {

	class PHX_API KeyEvent : public Event {

	public:
		inline int GetKeyCode() const { return keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : keyCode(keyCode) {}

		int keyCode;
	};

	class PHX_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) // ? Keep track of number of times repeated
			: KeyEvent(keyCode), repeatCount(repeatCount) {} // Key Repeat events

		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " pressed (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class PHX_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) // ? Keep track of number of times repeated
			: KeyEvent(keyCode) {} // Key Repeat events

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keyCode << " released";
			return ss.str();
		}

	};
}