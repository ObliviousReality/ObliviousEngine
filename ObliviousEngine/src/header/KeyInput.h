#pragma once
#include "EventHandler.h"
class KeyInput
{
public:
	KeyInput(EventHandler* handler);
	~KeyInput();
	void addKeyPress(OEKeys key);
	void removeKeyPress(OEKeys key);
	void addKeyRelease(OEKeys key);
	void removeKeyRelease(OEKeys key);
	void clearKeys();
	bool testEvent();

private:
	EventHandler* handler;
	int* keyPressList = new int[32];
	int keyPressLength = 0;
	int* keyReleaseList = new int[32];
	int keyReleaseLength = 0;
};

