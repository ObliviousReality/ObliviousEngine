#include "oepch.h"
#include "GLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>	

namespace OE
{
	GLTexture2D::GLTexture2D(const std::string& p) : path(p)
	{
		int w, h, cs;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &cs, 0);
		OE_CORE_ASSERT(data, "FAILED TO LOAD IMAGE");
		width = w;
		height = h;

		glCreateTextures(GL_TEXTURE_2D, 1, &renderID);
		glTextureStorage2D(renderID, 1, GL_RGB8, width, height);

		glTextureParameteri(renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(renderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(renderID, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}
	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &renderID);
	}
	void GLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, renderID);
	}
}