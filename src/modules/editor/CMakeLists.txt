add_executable(Editor
    src/editor.cpp

    include/editor.hpp
)

target_compile_options(Editor PRIVATE ${COMMON_COMPILE_OPTIONS})

# Зависимости редактора.
target_link_libraries(Editor PRIVATE
    Core
    Runtime
)