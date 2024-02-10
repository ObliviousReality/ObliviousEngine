#include "oepch.h"

#include "Platforms/OpenGL/GLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace OE
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		OE_PROFILE_FUNCTION();
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
		OE_CORE_ASSERT(false, "ERROR: Unknown Shader Type!");
		return 0;
	}

	GLShader::GLShader(const std::string& path)
	{
		OE_PROFILE_FUNCTION();
		std::string& shaderSource = readFile(path);
		auto srcs = preprocessFile(shaderSource);
		compile(srcs);

		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		name = path.substr(lastSlash, count);

	}
	GLShader::GLShader(const std::string& namein, const std::string& vertexSource, const std::string& fragmentSource) : name(namein)
	{
		OE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		compile(sources);
	}
	GLShader::~GLShader()
	{
		OE_PROFILE_FUNCTION();
		glDeleteProgram(renderID);
	}
	void GLShader::bind() const
	{
		OE_PROFILE_FUNCTION();
		glUseProgram(renderID);
	}
	void GLShader::unbind() const
	{
		OE_PROFILE_FUNCTION();
		glUseProgram(0);
	}
	void GLShader::setInt(const std::string& name, int val)
	{
		OE_PROFILE_FUNCTION();
		uploadUniformInt(name, val);
	}
	void GLShader::setMat4(const std::string& name, const glm::mat4& val)
	{
		OE_PROFILE_FUNCTION();
		uploadUniformMat4(name, val);
	}
	void GLShader::setFloat3(const std::string& name, const glm::vec3& val)
	{
		OE_PROFILE_FUNCTION();
		uploadUniformFloat3(name, val);
	}
	void GLShader::setFloat4(const std::string& name, const glm::vec4& val)
	{
		OE_PROFILE_FUNCTION();
		uploadUniformFloat4(name, val);
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
	std::string GLShader::readFile(const std::string& path)
	{
		OE_PROFILE_FUNCTION();
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], result.size());
				in.close();
			}
			else
			{
				OE_CORE_ERROR("ERROR: Could not read from file: {0}", path);
			}
		}
		else
		{
			OE_CORE_ERROR("ERROR: COULD NOT OPEN FILE '{0}'", path);
			return "";
		}
		return result;
	}
	std::unordered_map<GLenum, std::string> GLShader::preprocessFile(const std::string& src)
	{
		OE_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSrcs;

		const char* typeToken = "#type";
		size_t tokenLength = strlen(typeToken);
		size_t pos = src.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = src.find_first_of("\r\n", pos);
			OE_CORE_ASSERT(eol != std::string::npos, "SYNTAX ERROR WITH SHADER FILE");
			size_t begin = pos + tokenLength + 1;
			std::string type = src.substr(begin, eol - begin);
			OE_CORE_ASSERT(ShaderTypeFromString(type), "INVALID SHADER TYPE FOUND");

			size_t nextLinePos = src.find_first_not_of("\r\n", eol);
			OE_CORE_ASSERT(nextLinePos != std::string::npos, "ERROR WITH SHADER FILE");
			pos = src.find(typeToken, nextLinePos);
			shaderSrcs[ShaderTypeFromString(type)] = (pos == std::string::npos) ? src.substr(nextLinePos) : src.substr(nextLinePos, pos - nextLinePos);

		}
		return shaderSrcs;
	}
	void GLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		OE_PROFILE_FUNCTION();
		GLuint program = glCreateProgram();
		OE_CORE_ASSERT(shaderSrcs.size() <= 2, "ERROR: Too Many Shader Sources (Only 2 Allowed)");
		std::array<GLenum, 2> shaderIDs;
		int arrIndex = 0;
		for (auto& kv : shaderSrcs)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;
			//Source: https://www.khronos.org/opengl/wiki/Shader_Compilation#Example
			// (but modified)
			// 
			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = src.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				OE_CORE_ERROR("SHADER ERROR -> COMPILATION FAILURE: {0}", infoLog.data());
				OE_CORE_ASSERT(false, "DELETING VERTEX SHADER");
				// In this simple program, we'll just leave
				break;
			}
			// Attach our shaders to our program
			glAttachShader(program, shader);
			shaderIDs[arrIndex++] = shader;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		renderID = program;




		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto s : shaderIDs) {
				glDeleteShader(s);
			}

			// Use the infoLog as you see fit.
			OE_CORE_ERROR("SHADER ERROR -> LINK FAILURE: {0}", infoLog.data());
			OE_CORE_ASSERT(false, "DELETING SHADER");
			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (auto s : shaderIDs) {
			glDetachShader(program, s);
			glDeleteShader(s);
		}
	}
}