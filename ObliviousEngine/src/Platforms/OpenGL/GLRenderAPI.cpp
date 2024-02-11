#include "oepch.h"

#include "GLRenderAPI.h"

#include <glad/glad.h>

namespace OE
{
    void openGLMessageCallback(unsigned source,
                               unsigned type,
                               unsigned id,
                               unsigned severity,
                               int length,
                               const char * message,
                               const void * param)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
            {
                CORE_FATAL(message);
                return;
            }
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                CORE_ERROR(message);
                return;
            }
            case GL_DEBUG_SEVERITY_LOW:
            {
                CORE_WARN(message);
                return;
            }
            case GL_DEBUG_SEVERITY_NOTIFICATION:
            {
                CORE_TRACE(message);
                return;
            }
        }
        CORE_ASSERT(false, "UNKNOWN OPENGL MESSAGE SEVERITY LEVEL");
    }

    void GLRenderAPI::Init()
    {
        PROFILE_FUNCTION();
#ifdef LOG_GL_WARNINGS
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(openGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif // LOG_GL_WARNINGS
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void GLRenderAPI::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void GLRenderAPI::setClearColour(const Colour & colour) { glClearColor(colour.r, colour.g, colour.b, colour.a); }

    void GLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) { glViewport(x, y, w, h); }

    void GLRenderAPI::drawIndexed(const Ref<VertexArray> & arr)
    {
        glDrawElements(GL_TRIANGLES, arr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
} // namespace OE
