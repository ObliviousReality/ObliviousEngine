#pragma once
#include "Core.h"#

namespace OE {

	class OBLIVIOUSENGINE_API Object
	{
	public:
		Object();
		~Object();
		virtual void draw();
		virtual void update();
		virtual void onCollide(Object* e);

		virtual int getX();
		virtual int getY();
		virtual int getWidth();
		virtual int getHeight();

		virtual int getCollisionClass();

	protected:
		int x, y, w, h;
	};

}