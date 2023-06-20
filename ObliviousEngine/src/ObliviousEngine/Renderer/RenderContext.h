#pragma once

namespace OE
{
	class RenderContext 
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};

}