#include <pipeline/pipeline.hpp>

void Pipeline::add_system(System system)
{
    m_systems.push_back(std::move(system));
}

void Pipeline::run(entt::registry &registry, float dt)
{
    for (const auto &system : m_systems)
    {
        system(registry, dt);
    }
}