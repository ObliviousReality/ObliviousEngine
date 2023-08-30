#pragma once
#include <string>

#include <glm/glm.hpp>

namespace OE
{
	class GLShader
	{
	public:
		GLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~GLShader();

		void bind() const;
		void unbind() const;

		void uploadUniformMat4(const std::string& name,  const glm::mat4& matrix);
	private:
		uint32_t renderID;
	};
}