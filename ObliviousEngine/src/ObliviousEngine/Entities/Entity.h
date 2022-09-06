#pragma once
#include <SDL.h>
#include "ObliviousEngine/Renderer/Texture.h"
#include "Core.h"
#include "Object.h"
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE {

	class OBLIVIOUSENGINE_API Entity : public Object
	{
	public:
		Entity(int x, int y, Renderer* renderer);
		~Entity();

		Texture getTexture();
		virtual void setPos(int x, int y);
		virtual void draw();
		virtual void update();

		virtual double getArea();
		virtual double getCircumference();


	protected:
		Texture texture;
		int x, y;
	};

}