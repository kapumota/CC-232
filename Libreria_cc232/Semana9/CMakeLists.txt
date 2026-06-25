cmake_minimum_required(VERSION 3.20)

project(Semana9 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem9_headers INTERFACE)
target_include_directories(sem9_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sem9_headers INTERFACE cxx_std_17)

function(cc232_add_sem9_target target_name source_file)
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE sem9_headers)
endfunction()

# Demos basicos
cc232_add_sem9_target(sem9_demo_morin_representations "demos/demo_morin_representations.cpp")
cc232_add_sem9_target(sem9_demo_deng_search_framework "demos/demo_deng_search_framework.cpp")
cc232_add_sem9_target(sem9_demo_weighted_algorithms "demos/demo_weighted_algorithms.cpp")
cc232_add_sem9_target(sem9_demo_graph_variants "demos/demo_graph_variants.cpp")

# Pruebas
cc232_add_sem9_target(sem9_test_public "pruebas_publicas/test_public_week9.cpp")
cc232_add_sem9_target(sem9_test_internal "pruebas_internas/test_internal_week9.cpp")
cc232_add_sem9_target(sem9_test_weighted_algorithms "pruebas_internas/test_weighted_algorithms.cpp")
cc232_add_sem9_target(sem9_test_biconnected_components "pruebas_internas/test_biconnected_components.cpp")
cc232_add_sem9_target(sem9_test_graph_variants "pruebas_internas/test_graph_variants.cpp")

add_test(NAME semana9_public COMMAND sem9_test_public)
add_test(NAME semana9_internal COMMAND sem9_test_internal)
add_test(NAME semana9_weighted_algorithms COMMAND sem9_test_weighted_algorithms)
add_test(NAME semana9_biconnected_components COMMAND sem9_test_biconnected_components)
add_test(NAME semana9_graph_variants COMMAND sem9_test_graph_variants)
