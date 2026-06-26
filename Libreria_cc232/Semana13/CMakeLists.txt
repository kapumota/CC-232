cmake_minimum_required(VERSION 3.16)
project(Semana13CC232 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SEMANA13_STRICT_WARNINGS "Activar advertencias estrictas" ON)

function(configurar_objetivo_semana13 target_name)
    target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    if(SEMANA13_STRICT_WARNINGS)
        if(MSVC)
            target_compile_options(${target_name} PRIVATE /W4 /permissive-)
        else()
            target_compile_options(${target_name} PRIVATE -Wall -Wextra -pedantic)
        endif()
    endif()
endfunction()

set(SEMANA13_DEMOS
    demo_block_model
    demo_btree_insert
    demo_btree_delete
    demo_bplus_range_scan
    demo_bst_vs_btree
)

foreach(demo_name IN LISTS SEMANA13_DEMOS)
    add_executable(${demo_name} demos/${demo_name}.cpp)
    configurar_objetivo_semana13(${demo_name})
endforeach()

enable_testing()

add_executable(semana13_public pruebas_publicas/test_public_week13.cpp)
configurar_objetivo_semana13(semana13_public)
add_test(NAME semana13_public COMMAND semana13_public)

set(SEMANA13_INTERNAL_TESTS
    test_btree_insert_search
    test_btree_delete
    test_btree_invariants
    test_bplus_tree
    test_range_scan
    test_external_memory_cost
)

foreach(test_name IN LISTS SEMANA13_INTERNAL_TESTS)
    add_executable(semana13_${test_name} pruebas_internas/${test_name}.cpp)
    configurar_objetivo_semana13(semana13_${test_name})
    add_test(NAME semana13_${test_name} COMMAND semana13_${test_name})
endforeach()
