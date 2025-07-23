add_library(Physics STATIC
    src/world/physics_world.cpp
    src/systems/physics_creation.cpp
    src/systems/physics_update.cpp
    src/systems/physics_cleanup.cpp

    include/world/physics_world.hpp
    include/components/physics_component.hpp
    include/systems/physics_creation.hpp
    include/systems/physics_update.hpp
    include/systems/physics_cleanup.hpp
)

target_compile_options(Physics PRIVATE ${COMMON_COMPILE_OPTIONS})

target_include_directories(Physics PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${JoltPhysics_SOURCE_DIR}/..
)

target_link_libraries(Physics PRIVATE
    Jolt
    ECS
)

target_link_libraries(Physics PUBLIC
    glm
)