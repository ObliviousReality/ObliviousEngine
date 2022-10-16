#pragma once
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H


#include "Core.h"
#pragma warning(push, 0)
#include <SDL.h>
#pragma warning(pop)
#include <string>

namespace OE {

	const typedef enum {
		KEY_BKSP = '\b',
		KEY_TAB = '\t',
		KEY_RETURN = '\r',
		KEY_ESC = '\033',
		KEY_SPACE = ' ',
		KEY_HASH = '#',
		KEY_COMMA = ',',
		KEY_DASH = '-',
		KEY_PERIOD = '.',
		KEY_FWDSLASH = '/',
		KEY_0 = '0',
		KEY_1 = '1',
		KEY_2 = '2',
		KEY_3 = '3',
		KEY_4 = '4',
		KEY_5 = '5',
		KEY_6 = '6',
		KEY_7 = '7',
		KEY_8 = '8',
		KEY_9 = '9',
		KEY_SEMICOLON = ';',
		KEY_EQUALS = '=',
		KEY_LBRACKET = '[',
		KEY_BACKSLASH = '\\',
		KEY_RBRACKET = ']',
		KEY_QUOTE = '`',
		KEY_A = 'a',
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		KEY_DEL = '\177',

		KEY_CAPSLOCK = 1073741881,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,

		KEY_PRINTSCRN,
		KEY_SCROLLOCK,
		KEY_PAUSE,
		KEY_INSERT,
		KEY_HOME,
		KEY_PGUP,

		KEY_END = 1073741901,
		KEY_PGDOWN,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_NUMLOCK,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_MINUS,
		KEY_KP_PLUS,
		KEY_KP_ENTER,
		KEY_KP_1,
		KEY_KP_2,
		KEY_KP_3,
		KEY_KP_4,
		KEY_KP_5,
		KEY_KP_6,
		KEY_KP_7,
		KEY_KP_8,
		KEY_KP_9,
		KEY_KP_0,
		KEY_KP_PERIOD,

		KEY_MENU = 1073741925,
		KEY_LEFTCTRL = 1073742048,
		KEY_LEFTSHIFT,
		KEY_ALT,
		KEY_SYSTEM,
		KEY_RIGHTCTRL,
		KEY_RIGHTSHIFT,
		KEY_ALTGR
	} OEKeys;

	const typedef enum
	{
		LEFTMOUSE,
		MIDDLEMOUSE,
		RIGHTMOUSE,
		MOUSE4,
		MOUSE5
	} OEMouseButtons;


	class OBLIVIOUSENGINE_API EventHandler
	{
	public:
		EventHandler();
		void detectEvents();
		bool quitPressed();
		bool mouseMovedSinceLastFrame();
		int* getMouseXY();
		void resetKeys();
		int* getMouseInput();
		int* getPressedKeys();
		int getNumPressedKeys();
		int* getReleasedKeys();
		int getNumReleasedKeys();


	private:

		int* pressedKeys = new int[128];
		int keyPressIndex = 0;

		int* releasedKeys = new int[128];
		int keyReleaseIndex = 0;

		bool quit = false;
		bool mouseMoved = false;
		int mouseX = 0;
		int mouseY = 0;
		int* mouse = new int[5];
	};

}

#endif // !EVENTHANDLER_H