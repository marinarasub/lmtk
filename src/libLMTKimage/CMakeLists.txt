# CMakeLists.txt
# lmtk/src/libLMTKimage

cmake_minimum_required(VERSION 3.5)


#find_package(PNG)
find_package(ZLIB REQUIRED)
find_package(libpng CONFIG REQUIRED) 
find_package(JPEG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)


add_library(libLMTKimage
		STATIC
		"bokehblur.cpp"
		"boxblur.cpp"
		"chromakeyer.cpp"
		"color.cpp"
		"colorinvert.cpp"
		"convolution.cpp"
		"gaussianblur.cpp"
		"grayscale.cpp"
		"hslapixel.cpp"
		"huesatlum.cpp"
		"image.cpp"
        "imageshader.cpp"
		"jpeg.cpp"
		"pluginchain.cpp"
		"png.cpp"
		"rgbapixel.cpp"
		"sharpen.cpp")
		
target_include_directories(libLMTKimage PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(libLMTKimage PRIVATE ${JPEG_INCLUDE_DIR})
target_link_libraries(libLMTKimage PRIVATE png)
target_link_libraries(libLMTKimage PRIVATE ${JPEG_LIBRARIES})
target_link_libraries(libLMTKimage PRIVATE Eigen3::Eigen)
target_link_libraries(libLMTKimage PRIVATE utils)
