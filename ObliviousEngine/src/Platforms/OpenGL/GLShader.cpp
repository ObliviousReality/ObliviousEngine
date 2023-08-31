#include "oepch.h"

#include "GLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace OE
{
	GLShader::GLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		//Source: https://www.khronos.org/opengl/wiki/Shader_Compilation#Example
		// 
		// 
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			OE_CORE_ERROR("SHADER ERROR -> VERTEX COMPILATION FAILURE: {0}", infoLog.data());
			OE_CORE_ASSERT(false, "DELETING VERTEX SHADER");
			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			OE_CORE_ERROR("SHADER ERROR -> FRAGMENT COMPILATION FAILURE: {0}", infoLog.data());
			OE_CORE_ASSERT(false, "DELETING FRAGMENT SHADER (and vertex shader)");
			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		renderID = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(renderID, vertexShader);
		glAttachShader(renderID, fragmentShader);

		// Link our program
		glLinkProgram(renderID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(renderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(renderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(renderID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(renderID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			OE_CORE_ERROR("SHADER ERROR -> LINK FAILURE: {0}", infoLog.data());
			OE_CORE_ASSERT(false, "DELETING SHADER");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(renderID, vertexShader);
		glDetachShader(renderID, fragmentShader);
	}
	GLShader::~GLShader()
	{
		glDeleteProgram(renderID);
	}
	void GLShader::bind() const
	{
		glUseProgram(renderID);
	}
	void GLShader::unbind() const
	{
		glUseProgram(0);
	}
	void GLShader::uploadUniformInt(const std::string& name, int value)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniform1i(loc, value);
	}
	void GLShader::uploadUniformFloat(const std::string& name, float value)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniform1f(loc, value);
	}
	void GLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniform2f(loc, value.x, value.y);
	}
	void GLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniform3f(loc, value.x, value.y, value.z);
	}
	void GLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}
	void GLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void GLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint loc = glGetUniformLocation(renderID, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}