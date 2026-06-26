cmake_minimum_required(VERSION 3.20)

project(Semana11_CC232 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(cc232_semana11 INTERFACE)
target_include_directories(cc232_semana11 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(add_semana11_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE cc232_semana11)
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
endfunction()

add_semana11_executable(sem11_demo_trie_dictionary demos/demo_trie_dictionary.cpp)
add_semana11_executable(sem11_demo_autocomplete demos/demo_autocomplete.cpp)
add_semana11_executable(sem11_demo_string_matching demos/demo_string_matching.cpp)
add_semana11_executable(sem11_demo_suffix_structures demos/demo_suffix_structures.cpp)

add_semana11_executable(sem11_test_public pruebas_publicas/test_public_week11.cpp)
add_semana11_executable(sem11_test_trie_invariants pruebas_internas/test_trie_invariants.cpp)
add_semana11_executable(sem11_test_trie_map pruebas_internas/test_trie_map.cpp)
add_semana11_executable(sem11_test_string_matching pruebas_internas/test_string_matching.cpp)
add_semana11_executable(sem11_test_aho_corasick pruebas_internas/test_aho_corasick.cpp)
add_semana11_executable(sem11_test_suffix_structures pruebas_internas/test_suffix_structures.cpp)

add_test(NAME semana11_public COMMAND sem11_test_public)
add_test(NAME semana11_trie_invariants COMMAND sem11_test_trie_invariants)
add_test(NAME semana11_trie_map COMMAND sem11_test_trie_map)
add_test(NAME semana11_string_matching COMMAND sem11_test_string_matching)
add_test(NAME semana11_aho_corasick COMMAND sem11_test_aho_corasick)
add_test(NAME semana11_suffix_structures COMMAND sem11_test_suffix_structures)
