cmake_minimum_required(VERSION 3.16)
project(Semana14ProyectoIntegrador LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(semana14_headers INTERFACE)
target_include_directories(semana14_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

function(add_semana14_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE semana14_headers)
    target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic)
endfunction()

add_semana14_executable(demo_dictionary_advisor demos/demo_dictionary_advisor.cpp)
add_semana14_executable(demo_range_query_advisor demos/demo_range_query_advisor.cpp)
add_semana14_executable(demo_sorting_benchmark demos/demo_sorting_benchmark.cpp)
add_semana14_executable(demo_graph_benchmark demos/demo_graph_benchmark.cpp)
add_semana14_executable(demo_full_report demos/demo_full_report.cpp)

add_semana14_executable(semana14_public pruebas_publicas/test_public_week14.cpp)
add_test(NAME semana14_public COMMAND semana14_public)

add_semana14_executable(semana14_workload_profile pruebas_internas/test_workload_profile.cpp)
add_test(NAME semana14_workload_profile COMMAND semana14_workload_profile)

add_semana14_executable(semana14_benchmark_stats pruebas_internas/test_benchmark_stats.cpp)
add_test(NAME semana14_benchmark_stats COMMAND semana14_benchmark_stats)

add_semana14_executable(semana14_dictionary_advisor pruebas_internas/test_dictionary_advisor.cpp)
add_test(NAME semana14_dictionary_advisor COMMAND semana14_dictionary_advisor)

add_semana14_executable(semana14_range_query_advisor pruebas_internas/test_range_query_advisor.cpp)
add_test(NAME semana14_range_query_advisor COMMAND semana14_range_query_advisor)

add_semana14_executable(semana14_sorting_advisor pruebas_internas/test_sorting_advisor.cpp)
add_test(NAME semana14_sorting_advisor COMMAND semana14_sorting_advisor)

add_semana14_executable(semana14_report_generation pruebas_internas/test_report_generation.cpp)
add_test(NAME semana14_report_generation COMMAND semana14_report_generation)
