#pragma once
#include <string>

namespace OE
{
	class GLShader
	{
	public:
		GLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~GLShader();

		void bind() const;
		void unbind() const;
	private:
		uint32_t renderID;
	};
}