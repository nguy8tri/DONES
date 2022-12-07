cmake_minimum_required(VERSION 3.4...3.18)
project(DONES)

add_library(backend SHARED src/main.cpp src/matrix.cpp src/solve.cpp src/system.cpp)
set_target_properties(backend PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(translate src/translate.cpp)
target_link_libraries(translate PUBLIC backend)