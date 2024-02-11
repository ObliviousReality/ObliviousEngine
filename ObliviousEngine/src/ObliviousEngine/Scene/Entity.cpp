#include "oepch.h"

#include "Entity.h"

namespace OE
{
    Entity::Entity(entt::entity h, Scene * s) : handle(h), scene(s) {}
} // namespace OE
