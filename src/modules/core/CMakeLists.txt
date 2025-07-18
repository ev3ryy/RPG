add_library(Core STATIC
    src/platform/window.cpp

    include/logs.hpp
    include/platform/window.hpp
)

target_compile_options(Core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wnull-dereference
    -Wcast-align

    -Werror

    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    
    #$<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:-fsanitize=address;-fsanitize=undefined;-fno-omit-frame-pointer>
)

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

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    src/platform/window.cpp

    include/logs.hpp
    include/platform/window.hpp
)