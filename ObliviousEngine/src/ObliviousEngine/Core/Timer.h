#pragma once
#include <SDL.h>
#include "Core.h"

namespace OE {

	class OBLIVIOUSENGINE_API Timer
	{
	public:
		Timer();

		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();

		bool isStarted();
		bool isPaused();

	private:
		Uint32 startTicks;
		Uint32 pausedTicks;

		bool paused;
		bool started;
	};

}