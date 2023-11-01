#pragma once
#include <string>
#include <unordered_map>

namespace OE
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;

		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& namein, const std::string& vertexSource, const std::string& fragmentSource);

	};

	class ShaderLib
	{
	public:
		void add(const Ref<Shader>& shader);
		void add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> load(const std::string path); // Default name applied
		Ref<Shader> load(const std::string& name, const std::string path);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}