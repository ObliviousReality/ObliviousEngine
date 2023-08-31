#pragma once
#include <string>

#include <glm/glm.hpp>

namespace OE
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void bind() const;
		void unbind() const;

		void uploadUniformFloat4(const std::string& name, const glm::vec4& vec);
		void uploadUniformMat4(const std::string& name,  const glm::mat4& matrix);
	private:
		uint32_t renderID;
	};
}