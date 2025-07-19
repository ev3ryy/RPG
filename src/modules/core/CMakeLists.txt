add_library(Core STATIC
    src/window/window.cpp

    include/logs.hpp
    include/window/window.hpp
)

target_compile_options(Core PRIVATE ${COMMON_COMPILE_OPTIONS})

target_include_directories(Core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Core PRIVATE
    glfw
)

target_link_libraries(Core PUBLIC
    spdlog
    glm
)