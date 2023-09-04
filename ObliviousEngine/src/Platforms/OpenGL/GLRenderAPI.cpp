#include "oepch.h"
#include "GLRenderAPI.h"

#include <glad/glad.h>

namespace OE
{
	void GLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void GLRenderAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void GLRenderAPI::setClearColour(const Colour& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}
	void GLRenderAPI::drawIndexed(const Ref<VertexArray>& arr)
	{
		glDrawElements(GL_TRIANGLES, arr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}