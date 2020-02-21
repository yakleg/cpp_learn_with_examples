cmake_minimum_required(VERSION 3.0.0)
project(cpp_learn_with_examples VERSION 0.1.0)

include(CTest)
enable_testing()

set(EXAMPLES_ROOT ${PROJECT_SOURCE_DIR}/examples)

# Include Google Test configuration
include(${PROJECT_SOURCE_DIR}/cmake/gtest.cmake)
# Include cmake utilites
include(${PROJECT_SOURCE_DIR}/cmake/utilities.cmake)

add_example("c_arrays" ${EXAMPLES_ROOT}/c_arrays/c_arrays_test.cpp)
add_example("polymorphism_demonstration" ${EXAMPLES_ROOT}/concepts/oop/polymorphism/poliymorphism_test.cpp)
add_example("stack_demonstration" ${EXAMPLES_ROOT}/concepts/stack/stack_test.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
