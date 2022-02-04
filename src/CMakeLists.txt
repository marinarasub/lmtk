# CMakeLists.txt
# lmtk/src/
# includes any source directories as needed

cmake_minimum_required(VERSION 3.5)

# add libraries as needed
add_subdirectory("utils")
add_subdirectory("libLMTKimage")
add_subdirectory("libLMTKaudio")
#add_subdirectory("libLMTKvideo")
add_subdirectory("app")

#add main program