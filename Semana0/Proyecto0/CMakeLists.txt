cmake_minimum_required(VERSION 3.22)

project(cc232_proyecto0 LANGUAGES CXX)

option(BUILD_APPS "Compila demos de Proyecto0" ON)
option(BUILD_BENCHMARKS "Compila benchmarks de Proyecto0" ON)
option(CC232_ENABLE_WARNINGS "Activa advertencias estrictas" ON)
option(CC232_ENABLE_SANITIZERS "Activa ASan y UBSan" OFF)

include(CTest)
enable_testing()

add_library(cc232_proyecto0)

target_sources(cc232_proyecto0
    PRIVATE
        src/line_stats.cpp
        src/warmup_vector.cpp
)

target_compile_features(cc232_proyecto0
    PUBLIC
        cxx_std_17
)

target_include_directories(cc232_proyecto0
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CC232_ENABLE_WARNINGS)
    target_compile_options(cc232_proyecto0
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>
            $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )
endif()

if(CC232_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(cc232_proyecto0
            PUBLIC
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
        )
        target_link_options(cc232_proyecto0
            PUBLIC
                -fsanitize=address,undefined
        )
    else()
        message(WARNING "CC232_ENABLE_SANITIZERS está orientado a GCC, Clang o AppleClang.")
    endif()
endif()

add_executable(test_line_stats tests/test_line_stats.cpp)
target_link_libraries(test_line_stats PRIVATE cc232_proyecto0)
add_test(NAME test_line_stats COMMAND test_line_stats)

add_executable(test_warmup_vector tests/test_warmup_vector.cpp)
target_link_libraries(test_warmup_vector PRIVATE cc232_proyecto0)
add_test(NAME test_warmup_vector COMMAND test_warmup_vector)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_simple_array.cpp")
    add_executable(test_simple_array tests/test_simple_array.cpp)
    target_link_libraries(test_simple_array PRIVATE cc232_proyecto0)
    add_test(NAME test_simple_array COMMAND test_simple_array)
endif()

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

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_templates.cpp")
        add_executable(demo_templates apps/demo_templates.cpp)
        target_link_libraries(demo_templates PRIVATE cc232_proyecto0)
    endif()

    add_executable(demo_asan_out_of_bounds apps/demo_asan_out_of_bounds.cpp)
    target_link_libraries(demo_asan_out_of_bounds PRIVATE cc232_proyecto0)

    add_executable(demo_ubsan_overflow apps/demo_ubsan_overflow.cpp)
    target_link_libraries(demo_ubsan_overflow PRIVATE cc232_proyecto0)

    add_executable(demo_iterator_invalid apps/demo_iterator_invalid.cpp)
    target_link_libraries(demo_iterator_invalid PRIVATE cc232_proyecto0)
endif()

if(BUILD_BENCHMARKS)
    add_executable(bench_vector_growth bench/bench_vector_growth.cpp)
    target_link_libraries(bench_vector_growth PRIVATE cc232_proyecto0)

    add_executable(bench_vector_ops bench/bench_vector_ops.cpp)
    target_link_libraries(bench_vector_ops PRIVATE cc232_proyecto0)

    add_executable(bench_cache_effects bench/bench_cache_effects.cpp)
    target_link_libraries(bench_cache_effects PRIVATE cc232_proyecto0)
endif()

if(BUILD_APPS)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_vector_growth.cpp" AND NOT TARGET demo_vector_growth)
        add_executable(demo_vector_growth apps/demo_vector_growth.cpp)
        target_link_libraries(demo_vector_growth PRIVATE cc232_proyecto0)
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_iterator_invalidation.cpp" AND NOT TARGET demo_iterator_invalidation)
        add_executable(demo_iterator_invalidation apps/demo_iterator_invalidation.cpp)
        target_link_libraries(demo_iterator_invalidation PRIVATE cc232_proyecto0)
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/apps/demo_stl_algorithms.cpp" AND NOT TARGET demo_stl_algorithms)
        add_executable(demo_stl_algorithms apps/demo_stl_algorithms.cpp)
        target_link_libraries(demo_stl_algorithms PRIVATE cc232_proyecto0)
    endif()
endif()
