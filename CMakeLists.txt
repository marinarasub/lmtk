# CMakeLists.txt
# lmtk
# TOP LEVEL CMAKELISTS

# cmake minimum version
cmake_minimum_required(VERSION 3.5)


# get toolchain file
if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
	if (NOT CMAKE_TOOLCHAIN_FILE AND EXISTS ${vcpkg})
		set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "vcpkg toolchain file")
	endif()
endif()
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE for vcpkg not defined. Please specify VCPKG_ROOT or vcpkg.cmake file")
endif()

if(WIN32)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "Multithreaded$<CONFIG:Debug>:Debug") 
	set(CMAKE_MSVC_RUNTIME_LIBRARY "Multithreaded$<CONFIG:Release>:Release") 
endif()


# LMTK
project(LMTK VERSION 0.0.0)

# options...

#option(BUILD_32_BIT ON)
#option(BUILD_64_BIT ON)
#option(BUILD_IMG_LIB "Build image library" ON)
#option(BUILD_AUDIO_LIB "Build audio library" ON)
#option(BUILD_VIDEO_LIB "..." ON)
#option(BUILD_STATIC_LIBS ON)
option(BUILD_SHARED_LIBS OFF)
option(BUILD_TEST "Build Google Tests" OFF)
#option(BUILD_IMG_TESTS "Build image test executables" ON)
#option(BUILD_AUDIO_TESTS "Build audio test executables" ON)
#option(BUILD_IMG_EXAMPLES "Build image examples" ON) ...
#option(BUILD_VIDEO_TESTS "Build test executables" ON)
#option(WITH_STACK_PROTECTOR "Enable stack smash protection" ON)

set(VERSION ${CMAKE_PROJECT_VERSION})

configure_file("config.cmake.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

set(CMAKE_CXX_STANDARD 11 REQUIRED)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

#if (NOT BUILD_SHARED_LIBS) # doesn't do anything???
#    set(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
#endif()

#target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")


add_subdirectory("src")

if (BUILD_TEST)
	add_subdirectory("test")
endif()
 
#file(GLOB LMTK_HEADERS "include/*.h") # after add public headers
