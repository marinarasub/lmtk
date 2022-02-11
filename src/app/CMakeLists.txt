# CMakeLists.txt
# lmtk/src/app

cmake_minimum_required(VERSION 3.5)


find_package(Boost REQUIRED program_options)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

#add_executable(LMTKimage WIN32
#				"LMTKimage.cpp")

if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
endif()

add_executable(LMTKimage 
            "LMTKimage.cpp"
            "imagetools/progressbar.cpp"
            "imagetools/renderer.cpp"
            "imagetools/imagefx.cpp")
			
target_include_directories(LMTKimage PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(LMTKimage PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/imagetools")
target_link_libraries(LMTKimage PRIVATE Boost::program_options)
target_link_libraries(LMTKimage PRIVATE libLMTKimage)
target_link_libraries(LMTKimage PRIVATE utils)
