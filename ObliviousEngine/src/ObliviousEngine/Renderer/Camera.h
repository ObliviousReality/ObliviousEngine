#pragma once
#include "Core.h"

#include <glm/glm.hpp>

namespace OE
{
    class Camera
    {
    public:
        Camera(const glm::mat4 & _projection) : projection(_projection) {}

        const glm::mat4 getProjection() const { return projection; }

        // todo:

    private:
        glm::mat4 projection;
    };
} // namespace OE
