add_library(Runtime STATIC
    src/runtime.cpp

    include/runtime.hpp
)

target_compile_options(Runtime PRIVATE ${MY_COMMON_COMPILE_OPTIONS})

target_include_directories(Runtime PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(Runtime PRIVATE
    Core
)