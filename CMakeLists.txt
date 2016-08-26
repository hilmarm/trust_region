cmake_minimum_required(VERSION 3.2)
project(trust_region_alg LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH cmake)
find_package(Qt5Core REQUIRED)

include_directories(${Eigen_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/trust_lib")
add_subdirectory(trust_lib)

# Unit tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_trust
        tests/test_model.cpp)
target_link_libraries(test_trust
        TrustLib
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME test_trust COMMAND $<TARGET_FILE:test_trust>)
