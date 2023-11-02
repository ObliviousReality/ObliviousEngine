#pragma once
#include "oepch.h"
#include "Core.h"
namespace OE
{
	enum class EventType
	{
		None = 0,
		WinClose, WinResize, WinFocus, WinUnFocus, WinMove,
		AppTick, AppUpdate, AppRender,
		KeyDown, KeyUp, KeyType,
		MouseDown, MouseUp, MouseMove, MouseScroll
	};

	enum EventCategory
	{
		None = 0,
		ECApp = BIT(0),
		ECInput = BIT(1),
		ECKeyboard = BIT(2),
		ECMouse = BIT(3),
		ECMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CAT(cat) virtual int getCatFlags() const override { return cat; }

	class OBLIVIOUSENGINE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCatFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCat(EventCategory cat)
		{
			return getCatFlags() & cat;
		}

		bool handled = false;
	protected:
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e)
			: ev(e) {}

		template<typename T, typename F>
		bool dispatch(const F& func)
		{
			if (ev.getEventType() == T::getStaticType())
			{
				ev.handled = func(static_cast<T&>(ev));
				return true;
			}
			return false;
		}

	private:
		Event& ev;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}