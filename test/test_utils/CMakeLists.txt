# CMakeLists.txt
# lmtk/test/utilstest

add_executable(utilstest 
			"utilstest.cpp")

add_executable(ffttest
			"ffttest.cpp")

target_include_directories(utilstest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ffttest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(utilstest GTest::GTest GTest::Main)
target_link_libraries(utilstest utils)
target_link_libraries(ffttest GTest::GTest GTest::Main)
target_link_libraries(ffttest utils)

gtest_discover_tests(utilstest)
gtest_discover_tests(ffttest)