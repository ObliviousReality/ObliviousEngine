#pragma once
#ifndef COLOUR_H
#define COLOUR_H

#include "Core.h"
#include <glm/glm.hpp>
namespace OE {

	class Colour
	{
	public:
		Colour(float ri, float gi, float bi, float ai = 1.0f) : r(ri), g(gi), b(bi), a(ai) {}
		Colour(glm::vec4 vin) : r(vin.x), g(vin.y), b(vin.z), a(vin.w) {}
		Colour(glm::vec3 vin) : r(vin.x), g(vin.y), b(vin.z), a(1.0f) {}
		float getR() { return r; }
		float getG() { return g; }
		float getB() { return b; }
		float getA() { return a; }

		glm::vec4 getVec4() { return glm::vec4(r, g, b, a); }

		void setR(float newR) { r = newR; }
		void setG(float newG) { g = newG; }
		void setB(float newB) { b = newB; }
		void setA(float newA) { a = newA; }

		void setVec4(glm::vec4 v)
		{
			r = v.x;
			g = v.y;
			b = v.z;
			a = v.w;
		}


		operator glm::vec4() const { return glm::vec4(r, g, b, a); }
		operator glm::vec3() const { return glm::vec3(r, g, b); }

		float r, g, b, a;
	private:
	};

}

#endif // !COLOUR_H
