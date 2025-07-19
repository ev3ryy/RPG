#include <components/components.hpp>
#include <scene/scene.hpp>

entt::entity Scene::create_entity(const std::string &name)
{
    entt::entity entity = m_registry.create();

    m_registry.emplace<TransformComponent>(entity);
    m_registry.emplace<NameComponent>(entity, name.empty() ? "Entity" : name);

    return entity;
}