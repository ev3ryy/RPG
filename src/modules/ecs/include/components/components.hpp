#ifndef ECS_COMPONENTS_H
#define ECS_COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

struct TransformComponent
{
    float position_x, position_y, position_z;
    float rotation_x, rotation_y, rotation_z, rotation_w;

    TransformComponent()
        : position_x(0.0f), position_y(0.0f), position_z(0.0f), rotation_x(0.0f), rotation_y(0.0f), rotation_z(0.0f),
          rotation_w(1.0f)
    {
    }

    TransformComponent(float px, float py, float pz, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f, float rw = 1.0f)
        : position_x(px), position_y(py), position_z(pz), rotation_x(rx), rotation_y(ry), rotation_z(rz), rotation_w(rw)
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