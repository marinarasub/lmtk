# CMakeLists.txt
# lmtk/test/
# includes any test directories as needed

cmake_minimum_required(VERSION 3.5)

#include(CTest)
find_package(GTest REQUIRED)

include(GoogleTest)

enable_testing()

add_subdirectory("test_utils")
add_subdirectory("test_libLMTKimage")
add_subdirectory("test_libLMTKaudio")



