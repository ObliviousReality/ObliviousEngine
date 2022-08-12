#include "KeyInput.h"

namespace OE {

	KeyInput::KeyInput(EventHandler* handler)
	{
		this->handler = handler;
	}

	KeyInput::~KeyInput()
	{
	}

	void KeyInput::addKeyPress(OEKeys key)
	{
		keyPressList[keyPressLength] = key;
		keyPressLength++;
		if (keyPressLength > 31) {
			keyPressLength = 31;
		}
	}

	void KeyInput::removeKeyPress(OEKeys key)
	{
		int* tempList = keyPressList;
		keyPressLength = 0;
		for (int i = 0; i < 32; i++) {
			if (tempList[i] > 0) {
				if (tempList[i] != key) {
					keyPressList[i] = tempList[i];
					keyPressLength++;
				}
			}
			else {
				break;
			}
		}
	}

	void KeyInput::addKeyRelease(OEKeys key)
	{
		keyReleaseList[keyReleaseLength] = key;
		keyReleaseLength++;
		if (keyReleaseLength > 31) {
			keyReleaseLength = 31;
		}
	}

	void KeyInput::removeKeyRelease(OEKeys key)
	{
		int* tempList = keyReleaseList;
		keyReleaseLength = 0;
		for (int i = 0; i < 32; i++) {
			if (tempList[i] > 0) {
				if (tempList[i] != key) {
					keyReleaseList[i] = tempList[i];
					keyReleaseLength++;
				}
			}
			else {
				break;
			}
		}
	}

	void KeyInput::clearKeys()
	{
		keyPressLength = 0;
		keyReleaseLength = 0;
	}

	bool KeyInput::testEvent()
	{
		if (keyPressLength > 0) {
			int pressedKeysLength = handler->getNumPressedKeys();
			if (pressedKeysLength > 0) {
				int* pressedKeys = handler->getPressedKeys();
				for (int i = 0; i < pressedKeysLength; i++) {
					for (int j = 0; j < keyPressLength; j++) {
						if (pressedKeys[i] == keyPressList[j]) {
							return true;
						}
					}
				}
			}
		}
		else if (keyReleaseLength > 0) {
			int releasedKeysLength = handler->getNumReleasedKeys();
			if (releasedKeysLength > 0) {
				int* releasedKeys = handler->getReleasedKeys();
				for (int i = 0; i < releasedKeysLength; i++) {
					for (int j = 0; j < keyReleaseLength; j++) {
						if (releasedKeys[i] == keyReleaseList[j]) {
							return true;
						}
					}
				}
			}
		}
		return false;

	}

}