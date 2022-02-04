# CMakeLists.txt
# lmtk/test/test_liblmtkimage

cmake_minimum_required(VERSION 3.5)

add_executable(imagetest 
			"funtests.cpp"
			"hslapixeltest.cpp"
			"imagetest.cpp"
			"jpegtest.cpp"
			"pngtest.cpp"
			"rgbapixeltest.cpp")

add_executable(imageshadertest 
			"imageshadertest.cpp")

target_include_directories(imagetest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(imagetest GTest::GTest GTest::Main)
target_link_libraries(imagetest libLMTKimage)

target_include_directories(imageshadertest PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(imageshadertest GTest::GTest GTest::Main)
target_link_libraries(imageshadertest libLMTKimage)


gtest_discover_tests(imagetest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(imageshadertest WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
