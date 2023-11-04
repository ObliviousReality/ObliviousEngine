#pragma once
#include "ObliviousEngine/Renderer/Shader.h"

#include <glm/glm.hpp>

//TODO: REMOVE
typedef unsigned int GLenum;

namespace OE
{
	class GLShader : public Shader
	{
	public:
		GLShader(const std::string& path);
		GLShader(const std::string& namein, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~GLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setInt(const std::string& name, int val) override;
		virtual void setMat4(const std::string& name, const glm::mat4& val) override;
		virtual void setFloat3(const std::string& name, const glm::vec3& val) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& val) override;

		virtual const std::string& getName() const override { return name; }

		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> preprocessFile(const std::string& src);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
	private:
		uint32_t renderID;
		std::string name;
	};
}