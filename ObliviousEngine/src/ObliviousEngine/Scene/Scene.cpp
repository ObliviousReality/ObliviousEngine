#include "oepch.h"

#include "Components.h"
#include "Entity.h"
#include "Scene.h"

namespace OE
{
    Scene::Scene() {}

    Scene::~Scene() {}

    void Scene::update()
    {
        Camera * mainCam = nullptr;
        {
            auto group = registry.group<TransformComponent, CameraComponent>();
            for (auto cam : group)
            {
                CORE_TRACE("Item found");
                auto & [transform, camera] = group.get<TransformComponent, CameraComponent>(cam);

                if (camera.primary)
                {
                    mainCam = &camera.camera;
                    CORE_INFO("Main Camera Found");
                    break;
                }
            }
        }

        if (true)
        {
            CORE_TRACE("Main rendering loop section");
            auto group = registry.view<SpriteRendererComponent>();
            CORE_TRACE("Group Created.");
            for (auto g : group)
            {
                CORE_TRACE("Loop");
                auto sprite = group.get<SpriteRendererComponent>(g);
                Entity e = { g, this };
                auto transform = e.getComp<TransformComponent>();
            }
        }
        else
        {
            CORE_ERROR("No Camera in Scene, nothing drawn.");
        }
    }

    Entity Scene::createEntity(const std::string & name)
    {
        Entity temp = { registry.create(), this };
        temp.addComp<TransformComponent>();
        auto & tag = temp.addComp<TagComponent>();
        tag.tag = name.empty() ? "Unnamed Entity" : name;
        return temp;
    }
} // namespace OE
