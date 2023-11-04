#include "oepch.h"
#include "Platforms/OpenGL/GLTexture.h"

#include <stb_image.h>

namespace OE
{
	GLTexture2D::GLTexture2D(uint32_t w, uint32_t h)
		: width(w), height(h)
	{
		internalFormat = GL_RGBA8;
		format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &renderID);
		glTextureStorage2D(renderID, 1, internalFormat, width, height);

		glTextureParameteri(renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(renderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(renderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(renderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	GLTexture2D::GLTexture2D(const std::string& p) : path(p)
	{
		int w, h, cs;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &w, &h, &cs, 0);
		OE_CORE_ASSERT(data, "FAILED TO LOAD IMAGE");
		width = w;
		height = h;

		GLenum intFormat = 0, dataFormat = 0;
		if (cs == 4)
		{
			//RGBA
			intFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (cs == 3)
		{
			//RGB
			intFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		internalFormat = intFormat;
		format = dataFormat;

		OE_CORE_ASSERT(intFormat && dataFormat, "TEXTURE FORMAT NOT SUPPORTED");

		glCreateTextures(GL_TEXTURE_2D, 1, &renderID);
		glTextureStorage2D(renderID, 1, intFormat, width, height);

		glTextureParameteri(renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(renderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(renderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(renderID, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTextureSubImage2D(renderID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}
	GLTexture2D::~GLTexture2D()
	{
		glDeleteTextures(1, &renderID);
	}
	void GLTexture2D::setData(void* d, uint32_t size)
	{
		uint32_t bytesperpixel = format == GL_RGBA ? 4 : 3;
		OE_CORE_ASSERT(size == width * height * bytesperpixel, "ERROR: Data must be entire texture.");
		glTextureSubImage2D(renderID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, d);
	}
	void GLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, renderID);
	}
}