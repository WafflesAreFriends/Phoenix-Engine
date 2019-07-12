#pragma once

#include "Event.h"

namespace Phoenix {

	class PHX_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float posX, float posY) : posX(posX), posY(posY) {}

		inline float GetX() const { return posX; }
		inline float GetY() const { return posY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << "Mouse at (" << posX << ", " << posY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float posX, posY;
	};

	class PHX_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: xOffset(xOffset), yOffset(yOffset) {}

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << "Mouse scrolled (" << xOffset << ", " << yOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float xOffset, yOffset;
	};

	class PHX_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : button(button) {}
		int button;
	};

	class PHX_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class PHX_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}