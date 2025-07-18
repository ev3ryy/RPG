add_executable(Editor
    src/editor.cpp

    include/editor.hpp
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

# Зависимости редактора.
target_link_libraries(Editor PRIVATE
    Core
    Runtime
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    src/editor.cpp

    include/editor.hpp
)