add_library(IRenderer STATIC
    src/renderer.cpp
    src/api_selector.cpp
    src/vulkan/vulkan_renderer.cpp

    include/renderer.hpp
    include/api_selector.hpp
    include/vulkan_renderer.hpp
)

target_compile_options(IRenderer PRIVATE ${MY_COMMON_COMPILE_OPTIONS})

target_include_directories(IRenderer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)