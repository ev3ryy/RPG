#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

struct TransformComponent
{
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    TransformComponent() = default;
    TransformComponent(const glm::vec3 &pos, const glm::quat &rot, const glm::vec3 &s)
        : position(pos), rotation(rot), scale(s)
    {
    }
};

struct NameComponent
{
    std::string name;

    NameComponent() = default;
    NameComponent(const std::string &n) : name(n)
    {
    }
};

#endif // ECS_COMPONENTS_H