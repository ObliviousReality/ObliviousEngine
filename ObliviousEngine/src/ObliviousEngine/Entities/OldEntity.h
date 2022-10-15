#pragma once
#include <SDL.h>
#include "ObliviousEngine/Renderer/Texture.h"
#include "Core.h"
#include "Object.h"
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE {

	class OBLIVIOUSENGINE_API OldEntity : public Object
	{
	public:
		OldEntity(int x, int y, Renderer* renderer);
		~OldEntity();

		Texture getTexture();
		virtual void setPos(int x, int y);
		virtual void draw();
		virtual void update();
		virtual void onCollide(OldEntity* e);

		int getCollisionClass() override;

		virtual double getArea();
		virtual double getCircumference();

	protected:
		Texture texture;
	};

}