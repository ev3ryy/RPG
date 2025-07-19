add_library(Physics STATIC
    src/world/physics_world.cpp

    include/world/physics_world.hpp
    include/components/physics_component.hpp
)

target_compile_options(Physics PRIVATE ${COMMON_COMPILE_OPTIONS})

target_include_directories(Physics PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${JoltPhysics_SOURCE_DIR}/..
)

target_link_libraries(Physics PRIVATE
    Jolt
)

target_link_libraries(Physics PUBLIC
    glm
)