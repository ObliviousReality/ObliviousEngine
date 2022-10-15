#pragma once
#include "Core.h"
#include "OldEntity.h"
#include <ObliviousEngine/Renderer/Renderer.h>

namespace OE
{
	class OBLIVIOUSENGINE_API CircleEntity : public OldEntity
	{
	public:
		CircleEntity(int x, int y, int r, Renderer* renderer);
		~CircleEntity();

		void setRadius(int r);
		int getRadius(int r);

		double getArea() override;
		double getCircumference() override;

	private:
		int r;
	
	};
}

