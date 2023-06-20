#pragma once

#include "Core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Input 
	{
	public:
		inline static bool isKeyPressed(int KC) { return instance->isKeyPressedImp(KC); }
		inline static bool isMousePressed(int button) { return instance->isMousePressedImp(button); }
		inline static float getMouseX() { return instance->getMouseXImp(); }
		inline static float getMouseY() { return instance->getMouseYImp(); }
		inline static std::pair<float,float> GetMousePos() { return instance->getMousePosImp(); }


	protected:
		virtual bool isKeyPressedImp(int KC) = 0;
		virtual bool isMousePressedImp(int button) = 0;
		virtual float getMouseXImp() = 0;
		virtual float getMouseYImp() = 0;
		virtual std::pair<float, float> getMousePosImp() = 0;




	private:
		static Input* instance;
	};
}