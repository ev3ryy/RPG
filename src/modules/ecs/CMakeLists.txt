FetchContent_GetProperties(entt)

if(NOT entt_SOURCE_DIR)
    message(FATAL_ERROR "entt source directory not found. Please ensure FetchContent_MakeAvailable(entt) is called in the parent CMakeLists.txt")
endif()

add_library(ECS STATIC
    src/scene/scene.cpp
    src/pipeline/pipeline.cpp

    include/scene/scene.hpp
    include/components/components.hpp
    include/pipeline/pipeline.hpp
    include/pipeline/ISystem.hpp
)

target_compile_options(ECS PRIVATE ${COMMON_COMPILE_OPTIONS})

target_include_directories(ECS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${entt_SOURCE_DIR}/src
)

target_link_libraries(ECS PUBLIC
    glm
)