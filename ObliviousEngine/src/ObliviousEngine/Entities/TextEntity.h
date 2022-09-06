#pragma once
#include "Core.h"
#include "ObliviousEngine/Renderer/Text.h"
#include "Object.h"

namespace OE {

	class OBLIVIOUSENGINE_API TextEntity : public Object
	{
	public:
		TextEntity(int x, int y, Renderer* renderer);
		~TextEntity();

		Text getTexture();
		virtual void setPos(int x, int y);
		virtual void draw();
		virtual void update();

	protected:
		Text texture;
		int x, y, w, h;
	};

}