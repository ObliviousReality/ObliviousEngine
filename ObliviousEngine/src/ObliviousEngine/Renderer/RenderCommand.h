#pragma once
#include "RenderAPI.h"
namespace OE
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			rAPI->Init();
		}

		inline static void Clear()
		{
			rAPI->clear();
		}
		inline static void SetClearColour(const Colour& colour)
		{
			rAPI->setClearColour(colour);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& arr)
		{
			rAPI->drawIndexed(arr);
		}
	private:
		static RenderAPI* rAPI;
	};
}