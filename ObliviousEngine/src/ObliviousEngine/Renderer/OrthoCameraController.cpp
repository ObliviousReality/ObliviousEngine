#include "oepch.h"

#include "OrthoCameraController.h"

#include "ObliviousEngine/Core/Input.h"

#include "ObliviousEngine/Events/KeyCodes.h"

namespace OE
{
    OrthographicCameraController::OrthographicCameraController(float ratio, bool rotation) :
        aspectRatio(ratio), camera(-ratio * zoom, ratio * zoom, -zoom, zoom), rotate(rotation)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        PROFILE_FUNCTION();
        cameraSpeed = 2 * zoom;
        if (Input::isKeyPressed(KEY_A))
        {
            cameraPos.x -= cameraSpeed * ts;
        }
        if (Input::isKeyPressed(KEY_D))
        {
            cameraPos.x += cameraSpeed * ts;
        }
        if (Input::isKeyPressed(KEY_W))
        {
            cameraPos.y += cameraSpeed * ts;
        }
        if (Input::isKeyPressed(KEY_S))
        {
            cameraPos.y -= cameraSpeed * ts;
        }
        if (rotate)
        {
            if (Input::isKeyPressed(KEY_Q))
            {
                cameraRot += rotSpeed * ts;
            }
            if (Input::isKeyPressed(KEY_E))
            {
                cameraRot -= rotSpeed * ts;
            }
            camera.setRot(cameraRot);
        }
        if (Input::isKeyPressed(KEY_R))
        {
            cameraRot = 0;
            cameraPos.x = 0;
            cameraPos.y = 0;
            zoom = 1.0f;
            camera.setProj(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
        }
        camera.setPos(cameraPos);
    }

    void OrthographicCameraController::onEvent(Event & e)
    {
        PROFILE_FUNCTION();
        EventDispatcher d(e);
        d.dispatch<MouseScrollEvent>(BIND_EVENT(OrthographicCameraController::onMouseScroll));
        d.dispatch<WindowResizeEvent>(BIND_EVENT(OrthographicCameraController::onWindowResize));
    }

    bool OrthographicCameraController::onMouseScroll(MouseScrollEvent & mse)
    {
        PROFILE_FUNCTION();
        zoom -= mse.getYOff() * 0.25f;
        zoom = std::max(zoom, 0.25f);
        camera.setProj(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent & rse)
    {
        PROFILE_FUNCTION();
        aspectRatio = (float)rse.getWidth() / (float)rse.getHeight();
        camera.setProj(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
        return false;
    }
} // namespace OE
