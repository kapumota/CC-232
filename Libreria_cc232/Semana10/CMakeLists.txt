cmake_minimum_required(VERSION 3.20)

project(Semana10 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem10_headers INTERFACE)
target_include_directories(sem10_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sem10_headers INTERFACE cxx_std_17)

function(cc232_add_sem10_target target_name source_file)
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE sem10_headers)
endfunction()

# Demos basicos
cc232_add_sem10_target(sem10_demo_comparison_sorts "demos/demo_comparison_sorts.cpp")
cc232_add_sem10_target(sem10_demo_lower_bound "demos/demo_lower_bound.cpp")
cc232_add_sem10_target(sem10_demo_linear_sorts "demos/demo_linear_sorts.cpp")
cc232_add_sem10_target(sem10_demo_selection_and_intro "demos/demo_selection_and_intro.cpp")

# Pruebas
cc232_add_sem10_target(sem10_test_public "pruebas_publicas/test_public_week10.cpp")
cc232_add_sem10_target(sem10_test_internal "pruebas_internas/test_internal_week10.cpp")
cc232_add_sem10_target(sem10_test_stability_and_stats "pruebas_internas/test_stability_and_stats.cpp")
cc232_add_sem10_target(sem10_test_lower_bound "pruebas_internas/test_lower_bound.cpp")
cc232_add_sem10_target(sem10_test_linear_sorts "pruebas_internas/test_linear_sorts.cpp")
cc232_add_sem10_target(sem10_test_selection_intro "pruebas_internas/test_selection_intro.cpp")

add_test(NAME semana10_public COMMAND sem10_test_public)
add_test(NAME semana10_internal COMMAND sem10_test_internal)
add_test(NAME semana10_stability_and_stats COMMAND sem10_test_stability_and_stats)
add_test(NAME semana10_lower_bound COMMAND sem10_test_lower_bound)
add_test(NAME semana10_linear_sorts COMMAND sem10_test_linear_sorts)
add_test(NAME semana10_selection_intro COMMAND sem10_test_selection_intro)
