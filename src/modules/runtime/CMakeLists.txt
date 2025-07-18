add_library(Runtime STATIC
    src/engine.cpp

    include/engine.hpp
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

target_include_directories(Runtime PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Runtime PRIVATE
    Core
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    src/engine.cpp

    include/engine.hpp
)