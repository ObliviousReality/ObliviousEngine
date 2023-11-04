#include "oepch.h"
#include "ObliviousEngine/Renderer/Shader.h"

#include "ObliviousEngine/Renderer/Renderer.h"
#include "Platforms/OpenGL/GLShader.h"

namespace OE
{
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateRef<GLShader>(path);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
	Ref<Shader> Shader::Create(const std::string& namein, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			OE_CORE_ASSERT(false, "RENDERER API 'none' NOT SUPPORTED");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return CreateRef<GLShader>(namein, vertexSource, fragmentSource);
		default:
			OE_CORE_ASSERT(false, "UNKOWN RENDERER API SET");
			return nullptr;
		}
	}
	void ShaderLib::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		add(name, shader);
	}
	void ShaderLib::add(const std::string& name, const Ref<Shader>& shader)
	{
		OE_CORE_ASSERT(!exists(name), "ERROR: Shader Already Exists!");
		shaders[name] = shader;
	}
	Ref<Shader> ShaderLib::load(const std::string path)
	{
		auto s = Shader::Create(path);
		add(s);
		return s;
	}
	Ref<Shader> ShaderLib::load(const std::string& name, const std::string path)
	{
		auto s = Shader::Create(path);
		add(name, s);
		return s;
	}
	Ref<Shader> ShaderLib::get(const std::string& name)
	{
		OE_CORE_ASSERT(exists(name), "ERROR: Shader Doesn't Exist!");
		return shaders[name];
	}
	bool ShaderLib::exists(const std::string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}