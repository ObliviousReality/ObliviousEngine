#pragma once
#include "Core.h"
#include "Entity.h"
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE
{
	class OBLIVIOUSENGINE_API BoxEntity : public Entity
	{
	public:
		BoxEntity(int x, int y, int w, int h, Renderer* renderer);
		~BoxEntity();

		void setDimensions(int w, int h);
		void setHeight(int h);
		void setWidth(int w);
		int* getDimesions();
		int getHeight();
		int getWidth();

		double getArea() override;
		double getCircumference() override;

	protected:
		int w, h;
	};
}

