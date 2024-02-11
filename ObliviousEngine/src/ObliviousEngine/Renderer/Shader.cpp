#include "oepch.h"

#include "Renderer.h"
#include "Shader.h"

#include "Platforms/OpenGL/GLShader.h"

namespace OE
{
    Ref<Shader> Shader::Create(const std::string & path)
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None:
            {
                CORE_ASSERT(false, "RenderAPI::None IS NOT CURRENTLY SUPPORTED");
                return nullptr;
            }
            case RenderAPI::API::OpenGL:
            {
                return CreateRef<GLShader>(path);
            }
            default:
            {
                CORE_ASSERT(false, "UNKNOWN RENDERER API");
                return nullptr;
            }
        }
    }

    Ref<Shader>
        Shader::Create(const std::string & namein, const std::string & vertexSource, const std::string & fragmentSource)
    {
        switch (Renderer::GetAPI())
        {
            case RenderAPI::API::None:
            {
                CORE_ASSERT(false, "RenderAPI::None IS NOT CURRENTLY SUPPORTED");
                return nullptr;
            }
            case RenderAPI::API::OpenGL:
            {
                return CreateRef<GLShader>(namein, vertexSource, fragmentSource);
            }
            default:
            {
                CORE_ASSERT(false, "UNKNOWN RENDERER API");
                return nullptr;
            }
        }
    }

    void ShaderLib::add(const Ref<Shader> & shader)
    {
        auto & name = shader->getName();
        add(name, shader);
    }

    void ShaderLib::add(const std::string & name, const Ref<Shader> & shader)
    {
        CORE_ASSERT(!exists(name), "SHADER ALREADY EXISTS!");
        shaders[name] = shader;
    }

    Ref<Shader> ShaderLib::load(const std::string path)
    {
        auto s = Shader::Create(path);
        add(s);
        return s;
    }

    Ref<Shader> ShaderLib::load(const std::string & name, const std::string path)
    {
        auto s = Shader::Create(path);
        add(name, s);
        return s;
    }

    Ref<Shader> ShaderLib::get(const std::string & name)
    {
        CORE_ASSERT(exists(name), "SHADER DOESN'T EXIST!");
        return shaders[name];
    }

    bool ShaderLib::exists(const std::string & name) const { return shaders.find(name) != shaders.end(); }
} // namespace OE
