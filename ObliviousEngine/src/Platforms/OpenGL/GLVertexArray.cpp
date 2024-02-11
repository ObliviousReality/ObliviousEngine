#include "oepch.h"

#include "GLVertexArray.h"

#include <glad/glad.h>

namespace OE
{
    static GLenum ShaderTypeToGLType(ShaderType st)
    {
        switch (st)
        {
            case ShaderType::None: return 0;
            case ShaderType::Float: return GL_FLOAT;
            case ShaderType::Float2: return GL_FLOAT;
            case ShaderType::Float3: return GL_FLOAT;
            case ShaderType::Float4: return GL_FLOAT;
            case ShaderType::Mat3: return GL_FLOAT;
            case ShaderType::Mat4: return GL_FLOAT;
            case ShaderType::Int: return GL_INT;
            case ShaderType::Int2: return GL_INT;
            case ShaderType::Int3: return GL_INT;
            case ShaderType::Int4: return GL_INT;
            case ShaderType::Bool: return GL_BOOL;
            default: CORE_ASSERT(false, "UNKNOWN SHADER TYPE"); return 0;
        }
    }

    GLVertexArray::GLVertexArray()
    {
        PROFILE_FUNCTION();
        glCreateVertexArrays(1, &rendererID);
    }

    GLVertexArray::~GLVertexArray()
    {
        PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &rendererID);
    }

    void GLVertexArray::bind() const
    {
        PROFILE_FUNCTION();
        glBindVertexArray(rendererID);
    }

    void GLVertexArray::unbind() const
    {
        PROFILE_FUNCTION();
        glBindVertexArray(0);
    }

    void GLVertexArray::addVertexBuffer(const Ref<VertexBuffer> & buf)
    {
        PROFILE_FUNCTION();
        CORE_ASSERT(buf->getLayout().getElements().size(), "VERTEX BUFFER MISSING LAYOUT");
        glBindVertexArray(rendererID);
        buf->bind();
        uint32_t ind = 0;
        const auto & layout = buf->getLayout();
        for (const auto & element : layout)
        {
            glEnableVertexAttribArray(ind);
            glVertexAttribPointer(ind,
                                  element.getComponentCount(),
                                  ShaderTypeToGLType(element.type),
                                  element.normalised ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void *)element.offset);
            ind++;
        }
        vertexBufs.push_back(buf);
    }

    void GLVertexArray::setIndexBuffer(const Ref<IndexBuffer> & buf)
    {
        PROFILE_FUNCTION();
        glBindVertexArray(rendererID);
        buf->bind();
        indexBuf = buf;
    }
} // namespace OE
