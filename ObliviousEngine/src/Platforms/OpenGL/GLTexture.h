#pragma once

#include "ObliviousEngine/Renderer/Texture.h"

#include <glad/glad.h>

namespace OE
{
    class GLTexture2D : public Texture2D
    {
    public:
        GLTexture2D(uint32_t w, uint32_t h);
        GLTexture2D(const std::string & p);
        virtual ~GLTexture2D();

        virtual uint32_t getWidth() const override { return width; }
        virtual uint32_t getHeight() const override { return height; }

        virtual void setData(void * d, uint32_t size) override;

        virtual void bind(uint32_t slot = 0) const override;

    private:
        std::string path;

        uint32_t width, height;

        uint32_t renderID;

        GLenum internalFormat, format;
    };
} // namespace OE
