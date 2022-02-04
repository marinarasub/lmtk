# CMakeLists.txt
# lmtk/src/utils

cmake_minimum_required(VERSION 3.5)

find_package(Threads REQUIRED)

add_library(utils
			STATIC
			"fft.cpp"
			"utils.cpp"
			"utilsmath.cpp"
			"threadpool.cpp" 
			"file.cpp" "timer.h" "timer.cpp"  "utilsstring.h" "utilsstring.cpp")
			
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(utils Threads::Threads)
			