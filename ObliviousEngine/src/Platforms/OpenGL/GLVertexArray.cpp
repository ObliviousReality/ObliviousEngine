#include "oepch.h"
#include "GLVertexArray.h"

#include <glad/glad.h>

namespace OE
{

	static GLenum ShaderTypeToGLType(ShaderType st)
	{
		switch (st)
		{
		case OE::ShaderType::None:
			return 0;
		case OE::ShaderType::Float:
			return GL_FLOAT;
		case OE::ShaderType::Float2:
			return GL_FLOAT;
		case OE::ShaderType::Float3:
			return GL_FLOAT;
		case OE::ShaderType::Float4:
			return GL_FLOAT;
		case OE::ShaderType::Mat3:
			return GL_FLOAT;
		case OE::ShaderType::Mat4:
			return GL_FLOAT;
		case OE::ShaderType::Int:
			return GL_INT;
		case OE::ShaderType::Int2:
			return GL_INT;
		case OE::ShaderType::Int3:
			return GL_INT;
		case OE::ShaderType::Int4:
			return GL_INT;
		case OE::ShaderType::Bool:
			return GL_BOOL;
		default:
			OE_CORE_ASSERT(false, "UNKNOWN SHADER TYPE");
			return 0;
		}
	}
	GLVertexArray::GLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}
	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}
	void GLVertexArray::bind() const
	{
		glBindVertexArray(rendererID);
	}
	void GLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void GLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& buf)
	{
		OE_CORE_ASSERT(buf->getLayout().getElements().size(), "VERTEX BUFFER MISSING LAYOUT");
		glBindVertexArray(rendererID);
		buf->bind();
		uint32_t ind = 0;
		const auto& layout = buf->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(ind);
			glVertexAttribPointer(ind, element.getComponentCount(), ShaderTypeToGLType(element.type), element.normalised ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)element.offset);
			ind++;
		}
		vertexBufs.push_back(buf);

	}
	void GLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& buf)
	{
		glBindVertexArray(rendererID);
		buf->bind();
		indexBuf = buf;
	}
}