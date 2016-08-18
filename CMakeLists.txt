cmake_minimum_required(VERSION 3.5)
project(trust_region_alg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH cmake)

include_directories(${Eigen_INCLUDE_DIRS})
include_directories(${usr/include/RpolyPlusPlus})

find_package(Qt5Core REQUIRED)


set(SOURCE_FILES main.cpp region.cpp region.h model.cpp model.h polynomial.cpp polynomial.h)
add_executable(trust_region_alg ${SOURCE_FILES})
target_link_libraries(trust_region_alg Qt5::Core)