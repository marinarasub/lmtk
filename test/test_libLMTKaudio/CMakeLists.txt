# CMakeLists.txt
# lmtk/test/test_libLMTKaudio

cmake_minimum_required(VERSION 3.5)

add_executable(audiotest
			"audiotracktest.cpp")

target_include_directories(audiotest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(audiotest GTest::GTest GTest::Main)
target_link_libraries(audiotest libLMTKaudio)

gtest_discover_tests(audiotest)