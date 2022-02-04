# CMakeLists.txt
# lmtk/src/libLMTKaudio

cmake_minimum_required(VERSION 3.5)


find_package(flac CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)
#find_package(eigen3 CONFIG REQUIRED)


add_library(libLMTKaudio
		STATIC
		"audiofilter.cpp"
		"audioplayer.cpp"
		"audiotrack.cpp"
		"flac.cpp"
		"sawtooth.cpp"
		"sinewave.cpp"
		"squarewave.cpp")

target_include_directories(libLMTKaudio PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(libLMTKaudio PRIVATE utils)
target_link_libraries(libLMTKaudio PRIVATE FLAC::FLAC FLAC::FLAC++)
target_link_libraries(libLMTKaudio PRIVATE portaudio)
