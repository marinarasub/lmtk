/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in libLMTKimage, the image library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

/**
* @file image.h
* @author marinarasub
* @date December 2021
* @brief Class for representing an colored image in memory
*
* The image class represents a 2D canvas with color, and provides basic image 
* creation and modification.
*/


#ifndef _LIBLMTKIMAGE_IMAGE_H_
#define _LIBLMTKIMAGE_IMAGE_H_
#pragma once

#include <stdlib.h>
#include <stdexcept>
#include "rgbcolor.h"
#include "hslcolor.h"


namespace image {

//#define SUCCESS 0
//#define ERROR -1 // TODO don't use macros, use exceptions instead

    typedef unsigned char byte;

    /*
    * Enum for picking pixels outside of image dimensions
    *
    * DEFAULT is throw exception
    */
    enum class EdgeHandlingMethod 
    {
        NO_HANDLE,
        EXTEND,
        WRAP,
        TILE = WRAP,
        MIRROR,
        DEFAULT = NO_HANDLE
    };


    /**
    * Enum for resizing methods: nearest neighbor, linear, bicubic
    */
    enum class ResampleMethod {
        NEIGHBOR,
        BILINEAR,
        BICUBIC,
        DEFAULT = BILINEAR
    };

    // TODO image transformations

    /**
    * @class Image image.h
    * @brief Represents an rectangular, colored image.
    *
    * Image is of size width * height (OR x * y OR #columns * #rows). Stores color/
    * pixel data in RGBA format and provides basic image creation and modification
    * functions.
    *
    * @note The image class does not provide I/O (read/write) functions as it is
    * just a respresentation in memory. For such, use a class for a well defined
    * image file format.
    * @see RGBAPixel
    */
    class Image
    {
        /**
        * Struct for pixel data as a 1D array in memory where each row is stored
        * consecutively, top to bottom. The image has a defined width and height,
        * and such a pixel at location (x, y) is stored at index `y * width() + x`.
        *
        */
        struct pixel_array_struct
        {
            RGBAPixel* pixels;
            int width;
            int height;
        };


    public:
        /**
        * Creates an empty image of size 0 x 0.
        *
        * @note The pixel array is not initialized in this case. Must use
        * setInitialSize() to use image
        */
        Image();

        /**
        * Creates an image of size width * height.
        *
        * Each pixel is initialized to the default color with fillSolidColor()
        * The default is transparent.
        * @see fillSolidColor()
        * @param w Width
        * @param h Height
        */
        Image(int w, int h);

        /**
        * Creates an image by copying another image's data.
        *
        * @param other Image to copy
        */
        Image(const Image& other);

        /**
        * Deallocates dynamic memory used by image.
        *
        * Frees pixel data, calls clear()
        * @see clear()
        */
        virtual ~Image();

        /**
        * Assignment operator: sets this image to another image.
        *
        * If the two images are not the same already, calls copy()
        * @note can be overriden to check additional parameters
        * @see copy()
        */
        virtual Image operator=(const Image& other);

        /**
        * Equality operator: checks if two images are equal
        *
        * Two images are equal if they are the same width and height, and if every
        * single pixel is equal.
        * @note can be overriden to check additional parameters
        * @param other Image to be checked
        */
        virtual bool operator==(const Image& other) const;

        /**
        * Inequality operator: checks if two images are NOT equal.
        *
        * @see operator==
        * @param other Image to be checked
        */
        virtual bool operator!=(const Image& other) const;

        /**
        * Get the width of the image in pixels.
        *
        * @return Width of the image
        */
        int width() const;

        /**
        * Get the height of the image in pixels.
        *
        * @return Height of the image
        */
        int height() const;

        /**
        * Get the total size of the image in pixels.
        *
        * The size of the image is width * height
        * @return Size of the image
        */
        int size() const;

        /**
        * Fills the image with the given color
        *
        * Every pixel in the image is set to the given pixel, in RGBA
        * @param color The new color
        */
        void fillSolidColor(const RGBAPixel& color);

        // TODO add angles and raidal modes. Right now it is only vertical grad.
        // TODO arbitrary number of "color points", given location to start each.
        /**
        * Fills the a gradient from color1 to color2.
        *
        * Uses a linear gradient for each channel indepently with the difference
        * color2 - color1 in each channel R, G, B, A. The channel values may either
        * increase or decrease from color1, depending on if color2's value is larger
        * or smaller.
        * @param color1 The starting color
        * @param color2 The end color
        */
        void fillGradient(const RGBAPixel& color1, const RGBAPixel& color2);

        // TODO specify location to place
        /**
        * Blends the given image on top of this one, including alpha.
        *
        * The current (this) image is modified by blending every pixel with the
        * corresponding color in the other image, proportional to the alpha of each.
        * This is done until the other image has no remaining pixels. If the other
        * image is larger, any remnant pixels are ignored.
        * @note If the blending pixel's alpha is 1.0, the current will be replaced
        * @param color1 The starting color
        * @param color2 The end color
        */
        void blendNormal(const Image& other);

        // TODO bicubic, linear resample
        /**
        * Resizes the current image to specified width and height, in pixels.
        *
        * Resizing is done using nearest neighbor resampling
        * @note Should not be resized to 0 * 0
        * @param w New width
        * @param h New height
        */
        void resize(int w, int h); // calls default
        void resize(int w, int h, ResampleMethod method); // will call scale resize
        // calls getPixel with a interp. method (accepts floats)
        // TODO downsampling

        /**
        * Scales the width and height of the image by a specified amount.
        *
        * Calculates the new width and height and calls resize()
        * @see resize()
        * @note Should not scale by 0
        * @param scale_x Width scale
        * @param scale_y Height scale
        */
        void scale(float scale_x, float scale_y);

        // TODO crop and size
        // void crop(); upper left and lower right
        //

        // TODO flip horizontal
        /**
        * Flips the image across an axis
        */
        void mirror(); // flip across one axis

        // TODO rotate (more complicated, need matrix math and resampling)
        //

        // TODO may return color instead of ptr in future
        /**
        * Returns a pointer to the pixel at (x, y).
        *
        * @see pixelAt()
        * @param x X position of pixel
        * @param y Y position of pixel
        * @return A pointer to the pixel at (x, y)
        * @throw an exception if the pixel does not exist
        */
        RGBAPixel* getRGBAPixel(int x, int y) const;

        /**
        * Returns pixel at (x, y) if exists, else depends on edge handling.
        *
        * @see getRGBAPixel()
        * @param x X position of pixel
        * @param y Y position of pixel
        * @param edge_method The edge handling method
        * @see EdgeHandlingMethod
        * @return The pixel at (x, y) if exists, else use edge handling method
        */
        RGBAPixel getRGBAPixel(int x, int y, EdgeHandlingMethod edge_method) const;

        /**
        * Returns pixel at resampled pixel at (x, y)
        *
        * @see getRGBAPixel()
        * @param x X position of pixel
        * @param y Y position of pixel
        * @param method The resampling method
        * @see ResampleMethod
        * @return The sampled pixel at (x, y) using a resample method
        */
        RGBAPixel getRGBAPixel(float x, float y, ResampleMethod method) const;
        
        // TODO get HSLA?

        /**
        * Attempts to set the pixel at (x, y) to the given color.
        *
        * @see pixelAt()
        * @param color RGBA Color to set the pixel to
        * @param x X position of pixel
        * @param y Y position of pixel
        * @return True if the color of the pixel was changed, false otherwise
        */
        bool setRGBAPixel(const RGBAPixel& color, int x, int y);

        /**
        * Attempts to set the pixel at (x, y) to the given color.
        *
        * @see pixelAt()
        * @param color HSLA Color to set the pixel to
        * @param x X position of pixel
        * @param y Y position of pixel
        * @return True if the color of the pixel was changed, false otherwise
        */
        bool setHSLAPixel(const HSLAPixel& color, int x, int y);

        /**
        * Returns a string representation of the image.
        *
        * @note This function is subject to change.
        * @return The string representation
        */
        std::string to_string();


    protected:

        // lower level functions for read/write
        /**
        * return pointer to start or row.
        */
        RGBAPixel* getRow(int row_num) const;

        // caller's responsibility to make sure row_width is correct
        // if row_wdith > width(), ignore. < then stop at row_width
        bool setRow(RGBAPixel row_pixels[], size_t row_width, int row_num);

        /**
        * Returns a pointer to the pixel at (x, y), if exists.
        *
        * @param x X position
        * @param y Y position
        * @return Pointer to pixel at (x, y) or nullptr if out of bounds
        */
        RGBAPixel* pixelAt(int x, int y) const;

        /**
        * Helper for resampling of color at x, y using bilinear resample.
        */
        RGBAPixel bilinearResample(float x, float y) const;

        // TODO
        RGBAPixel bicubicResample(float x, float y) const;
        
        // TODO mipmap, box (downsampling)

        /**
        * Attempts to set the size of the image and allocates memory for pixel data.
        *
        * @warning Should only be used if necessary, and call clear() before using
        * or else will memory leak.
        * @throw an exception!!! if the width or height given is 0
        * @throw an exception!!! if malloc returns NULL
        */
        void setInitialSize(int w, int h);

        /**
        * Copies the current image to match the given image
        *
        * Old image data is freed with clear() before allocating space for the
        * size of the image to copy, Then calls setInitialSize()
        * @see clear()
        * @see setInitialSize()
        */
        virtual void copy(const Image&);

        /**
        * Frees the pixel data, if it is not NULL
        *
        * Sets the pixel data pointer to NULL after completion.
        */
        virtual void clear();

        pixel_array_struct pixel_data; /**< The image pixel data */
    };

}

#endif // _LIBLMTKIMAGE_IMAGE_H_