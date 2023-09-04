#pragma once
#include "ObliviousEngine/Renderer/RenderAPI.h"

namespace OE
{
	class GLRenderAPI : public RenderAPI
	{
	public:
		virtual void clear() override;
		virtual void setClearColour(const Colour& colour) override;

		virtual void drawIndexed(const Ref<VertexArray>& arr) override;
	};
}