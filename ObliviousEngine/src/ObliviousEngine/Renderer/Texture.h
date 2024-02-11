#pragma once

namespace OE
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setData(void * d, uint32_t size) = 0;

        virtual void bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string & p);
        static Ref<Texture2D> Create(uint32_t w, uint32_t h);
    };
} // namespace OE
