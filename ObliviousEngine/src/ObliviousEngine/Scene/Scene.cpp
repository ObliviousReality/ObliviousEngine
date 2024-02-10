#include "oepch.h"

#include "Entity.h"
#include "Scene.h"

#include <ObliviousEngine/Scene/Components.h>

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
                OE_CORE_TRACE("Item found");
                auto & [transform, camera] = group.get<TransformComponent, CameraComponent>(cam);

                if (camera.primary)
                {
                    mainCam = &camera.camera;
                    OE_CORE_INFO("Main Camera Found");
                    break;
                }
            }
        }

        if (true)
        {
            OE_CORE_TRACE("Main rendering loop section");
            auto group = registry.view<SpriteRendererComponent>();
            OE_CORE_TRACE("Group Created.");
            for (auto g : group)
            {
                OE_CORE_TRACE("Loop");
                auto sprite = group.get<SpriteRendererComponent>(g);
                Entity e = { g, this };
                auto transform = e.getComp<TransformComponent>();
            }
        }
        else
        {
            OE_CORE_ERROR("No Camera in Scene, nothing drawn.");
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
