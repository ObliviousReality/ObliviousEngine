#pragma once
//#include "oepch.h"
#include "Event.h"
namespace OE
{
	class OBLIVIOUSENGINE_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return keyCode; }

		EVENT_CLASS_CAT(ECKeyboard | ECInput);

	protected:
		KeyEvent(int kc)
			: keyCode(kc) {}

		int keyCode;
	};

	class OBLIVIOUSENGINE_API KeyDownEvent : public KeyEvent
	{
	public:
		KeyDownEvent(int kc, int repCount) 
			: KeyEvent(kc), repeatCount(repCount) {}

		inline int getRepCount() const { return repeatCount; }
		
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << keyCode << " (" << repeatCount << " times).";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyDown);

	private:
		int repeatCount;
	};

	class OBLIVIOUSENGINE_API KeyUpEvent : public KeyEvent
	{
		KeyUpEvent(int kc)
			: KeyEvent(kc) {}

		std::string toString() const override 
		{
			std::stringstream ss;
			ss << "KeyUpEvent: " << keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyUp);
	};
}