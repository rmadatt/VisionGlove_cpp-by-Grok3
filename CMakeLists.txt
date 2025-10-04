cmake_minimum_required(VERSION 3.15)
project(simd_modules)
find_package(pybind11 REQUIRED)
include_directories(path/to/eve/include)  # Adjust as needed
pybind11_add_module(simd_modules src/simd_gesture.cpp src/simd_threat.cpp)
