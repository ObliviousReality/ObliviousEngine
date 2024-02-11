#include "oepch.h"

#include "Platforms/OpenGL/GLTexture.h"

#include <stb_image.h>

namespace OE
{
    GLTexture2D::GLTexture2D(uint32_t w, uint32_t h) : width(w), height(h)
    {
        PROFILE_FUNCTION();
        internalFormat = GL_RGBA8;
        format = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &renderID);
        glTextureStorage2D(renderID, 1, internalFormat, width, height);

        glTextureParameteri(renderID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(renderID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(renderID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(renderID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    GLTexture2D::GLTexture2D(const std::string & p) : path(p)
    {
        PROFILE_FUNCTION();
        int w, h, cs;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc * data = nullptr;
        {
            PROFILE_SCOPE("stbi_load @ GLTexture2D::GLTexture2D(const std::string& p)");

            data = stbi_load(path.c_str(), &w, &h, &cs, 0);
        }
        CORE_ASSERT(data, "FAILED TO LOAD IMAGE");
        width = w;
        height = h;

        GLenum intFormat = 0, dataFormat = 0;
        if (cs == 4)
        {
            // RGBA
            intFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (cs == 3)
        {
            // RGB
            intFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        internalFormat = intFormat;
        format = dataFormat;

        CORE_ASSERT(intFormat && dataFormat, "TEXTURE FORMAT NOT SUPPORTED");

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
        PROFILE_FUNCTION();
        glDeleteTextures(1, &renderID);
    }

    void GLTexture2D::setData(void * d, uint32_t size)
    {
        PROFILE_FUNCTION();
        uint32_t bytesperpixel = format == GL_RGBA ? 4 : 3;
        CORE_ASSERT(size == width * height * bytesperpixel, "DATA MUST BE ENTIRE TEXTURE");
        glTextureSubImage2D(renderID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, d);
    }

    void GLTexture2D::bind(uint32_t slot) const
    {
        PROFILE_FUNCTION();
        glBindTextureUnit(slot, renderID);
    }
} // namespace OE
