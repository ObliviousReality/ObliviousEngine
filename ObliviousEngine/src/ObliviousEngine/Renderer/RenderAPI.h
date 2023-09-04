#pragma once
#include "Colour.h"
#include "VertexArray.h"
namespace OE
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void clear() = 0;
		virtual void setClearColour(const Colour& colour) = 0;

		virtual void drawIndexed(const Ref<VertexArray>& arr) = 0;

		inline static API GetAPI() { return activeAPI; }

	private:
		static API activeAPI;
	};
}