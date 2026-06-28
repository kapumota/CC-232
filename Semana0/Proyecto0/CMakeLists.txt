cmake_minimum_required(VERSION 3.22)

project(cc232_proyecto0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_BENCHMARKS "Build benchmark targets" ON)
option(BUILD_APPS "Build demo applications" ON)

include(CTest)
enable_testing()

add_library(cc232_proyecto0
    src/line_stats.cpp
    src/warmup_vector.cpp
)

target_include_directories(cc232_proyecto0 PUBLIC include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cc232_proyecto0 PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(test_line_stats tests/test_line_stats.cpp)
target_link_libraries(test_line_stats PRIVATE cc232_proyecto0)
add_test(NAME test_line_stats COMMAND $<TARGET_FILE:test_line_stats>)

add_executable(test_warmup_vector tests/test_warmup_vector.cpp)
target_link_libraries(test_warmup_vector PRIVATE cc232_proyecto0)
add_test(NAME test_warmup_vector COMMAND $<TARGET_FILE:test_warmup_vector>)

add_executable(test_simple_array tests/test_simple_array.cpp)
target_link_libraries(test_simple_array PRIVATE cc232_proyecto0)
add_test(NAME test_simple_array COMMAND $<TARGET_FILE:test_simple_array>)

if(BUILD_APPS)
    add_executable(demo_line_stats apps/demo_line_stats.cpp)
    target_link_libraries(demo_line_stats PRIVATE cc232_proyecto0)

    add_executable(demo_const_refs apps/demo_const_refs.cpp)
    target_link_libraries(demo_const_refs PRIVATE cc232_proyecto0)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_copy_semantics.cpp")
        add_executable(demo_copy_semantics apps/demo_copy_semantics.cpp)
        target_link_libraries(demo_copy_semantics PRIVATE cc232_proyecto0)
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_raii.cpp")
        add_executable(demo_raii apps/demo_raii.cpp)
        target_link_libraries(demo_raii PRIVATE cc232_proyecto0)
    endif()

    add_executable(demo_templates apps/demo_templates.cpp)
    target_link_libraries(demo_templates PRIVATE cc232_proyecto0)
endif()

if(BUILD_BENCHMARKS)
    add_executable(bench_vector_growth bench/bench_vector_growth.cpp)
    target_link_libraries(bench_vector_growth PRIVATE cc232_proyecto0)

    add_executable(bench_vector_ops bench/bench_vector_ops.cpp)
    target_link_libraries(bench_vector_ops PRIVATE cc232_proyecto0)

    add_executable(bench_cache_effects bench/bench_cache_effects.cpp)
    target_link_libraries(bench_cache_effects PRIVATE cc232_proyecto0)
endif()
