#pragma once

#include "Phoenix/Core.h"

namespace Phoenix {

	// Currently blocking events. Better strategy to buffer events in an event bus and process them during the event part of the update stage.

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory { // Filters Events
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class PHX_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0; // Type of event
		virtual const char* GetName() const = 0; // Name of event
		virtual int GetCategoryFlags() const = 0; // Category of event
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
		inline bool IsHandled() const { return handled; }

	protected:
		bool handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : event(event) {}

		// Makes sure T is an event and handles it
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (event.GetEventType() == T::GetStaticType()) {
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	// Event print
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}