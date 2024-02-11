#include "oepch.h"

#include "GLBuffer.h"

#include <glad/glad.h>

namespace OE
{
    GLVertexBuffer::GLVertexBuffer(float * vertexes, uint32_t size)
    {
        OE_PROFILE_FUNCTION();
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertexes, GL_STATIC_DRAW);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        OE_PROFILE_FUNCTION();
        glDeleteBuffers(1, &rendererID);
    }

    void GLVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, rendererID); }

    void GLVertexBuffer::unbind() const
    {
        OE_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLIndexBuffer::GLIndexBuffer(uint32_t * indexes, uint32_t count_in) : count(count_in)
    {
        OE_PROFILE_FUNCTION();
        glCreateBuffers(1, &rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indexes, GL_STATIC_DRAW);
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        OE_PROFILE_FUNCTION();
        glDeleteBuffers(1, &rendererID);
    }

    void GLIndexBuffer::bind() const
    {
        OE_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void GLIndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
} // namespace OE
