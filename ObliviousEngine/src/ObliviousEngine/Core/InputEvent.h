#pragma once
#ifndef KEYINPUT_H
#define KEYINPUT_H


#include "Core.h"
#include "EventHandler.h"

namespace OE {

	class OBLIVIOUSENGINE_API InputEvent
	{
	public:
		InputEvent(EventHandler* handler);
		~InputEvent();
		void addKeyPress(OEKeys key);
		void removeKeyPress(OEKeys key);
		void addKeyRelease(OEKeys key);
		void removeKeyRelease(OEKeys key);
		void addMouseClick(OEMouseButtons button);
		void removeMouseClick(OEMouseButtons button);
		void clearKeys();
		bool testEvent();

	private:
		EventHandler* handler;
		int* keyPressList = new int[32];
		int keyPressLength = 0;
		int* keyReleaseList = new int[32];
		int keyReleaseLength = 0;
		int* mouseClickList = new int[5];
		int mouseClickLength = 0;
	};

}

#endif // !KEYINPUT_H