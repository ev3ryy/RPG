cmake_minimum_required(VERSION 3.15)

project(RPG VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# FetchContent_Declare(
#     stb_image
#     GIT_REPOSITORY https://github.com/nothings/stb.git
#     GIT_SUBDIRECTORY "stb_image"
#     GIT_TAG master
# )
# FetchContent_MakeAvailable(stb_image)

# FetchContent_Declare(
#     imgui
#     GIT_REPOSITORY https://github.com/ocornut/imgui.git
#     GIT_TAG v1.92.1
# )
# FetchContent_MakeAvailable(imgui)

# FetchContent_Declare(
#     entt
#     GIT_REPOSITORY https://github.com/skypjack/entt.git
#     GIT_TAG v3.15.0
# )
# FetchContent_MakeAvailable(entt)

# FetchContent_Declare(
#     assimp
#     GIT_REPOSITORY https://github.com/assimp/assimp.git
#     GIT_TAG v6.0.2
# )
# FetchContent_MakeAvailable(assimp)

# FetchContent_Declare(
#     jolt_physics
#     GIT_REPOSITORY https://github.com/jrouwe/JoltPhysics.git
#     GIT_TAG v5.3.0
# )
# FetchContent_MakeAvailable(jolt_physics)

add_subdirectory(src/modules/core)
# add_subdirectory(src/modules/input)
# add_subdirectory(src/modules/renderer)
# add_subdirectory(src/modules/assetmanagement)
# add_subdirectory(src/modules/physics)
# add_subdirectory(src/modules/animation)
# add_subdirectory(src/modules/ecs)
add_subdirectory(src/modules/runtime)
add_subdirectory(src/modules/editor)