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
 * @file convolution.h
 * @author marinarasub
 * @date December 2021
 * @brief File containing the base class for convolution filtering
 *
 * @see imageshader.h
 */


#ifndef _LIBLMTKIMAGE_CONVOLUTION_H_
#define _LIBLMTKIMAGE_CONVOLUTION_H_
#pragma once

#include <Eigen/Dense>
#include "imageshader.h"

namespace image {

    // TODO seperate kernels for each channel

    /*
    * Convolution Example:
    * 
    * Ex Identity   0 0 0   1 2 3
    *               0 1 0 * 4 5 6 = 5
    *               0 0 0   7 8 9
    * 
    * Ex Box        1 1 1   1 2 3
    *               1 1 1 * 4 5 6 = 45
    *               1 1 1   7 8 9
    */

    /**
    * @class ImageConvolution "convolution.h"
    * @brief Base class for all image filters using convolution/kernel filtering
    * 
    * Image convolution uses a kernel, which is a m * n matrix of weights.
    * For each pixel in a image, a new pixel is calculated using weights at
    * the corresponding (row, col) in the kernel, where the original pixel is
    * the center.
    * 
    * This implementation guarentees an odd n and m for a well defined center.
    * @note Time complexity of one pixel is O(n * m)
    */
    class ImageConvolution : public ImageShader
    {
    public:

        /**
        * Creates the default image convolution.
        * 
        * A 1 * 1 matrix
        */
        ImageConvolution();

        /**
        * Creates a image convolution with kernel center at (center, center).
        * 
        * @see setKernelSize()
        * @param center The center row and column
        */
        ImageConvolution(size_t center);

        /**
        * Creates an image convolution with kernel center at (centerX, centerY).
        * 
        * @see setKernelSize()
        * @param centerX The center column
        * @param centerY The center row
        */
        ImageConvolution(size_t centerX, size_t centerY);

        /**
        * Creates an image convolution with kernel center and edge handling 
        * method for boundary pixels convolving outside the image.
        * 
        * @see EdgeHandlingMethod
        * @param centerX The center column
        * @param centerY The center row
        * @param edge_method The edge handling method
        */
        ImageConvolution(size_t centerX, size_t centerY,
            EdgeHandlingMethod edge_method);

        /**
        * Convolves the entire image
        * 
        * Uses the RGBAPixel operator() on each pixel in the given image.
        * @param img Image to operate on
        */
        virtual void operator()(Image& img) override;

        /**
        * Virtual convolution operator returns the result pixel at x, y.
        * 
        * Performs convolution using the kernel at x, y on given image with
        * surrounding pixels.
        * 
        * @see convolution()
        * @param img Image to operate over
        * @param x X location of target pixel
        * @param y Y location of target pixel
        * @returns Resulting convolved pixel
        */
        virtual RGBAPixel operator()(const Image& img, size_t x, size_t y) 
            override;

    protected:

        /*
        * Sizing Example:
        * 
        * Ex center = 0, 0  0
        * 
        * Ex center = 1, 1  0 0 0
        *                   0 c 0
        *                   0 0 0
        * 
        * Ex center = 2, 3  0 0 0 0 0
        *                   0 0 0 0 0
        *                   0 0 0 0 0
        *                   0 0 c 0 0
        *                   0 0 0 0 0
        *                   0 0 0 0 0
        *                   0 0 0 0 0
        */

        /**
        * Sets the kernel size using a given integral center row and column.
        * 
        * This guarentees and odd number of rows and columns
        * 
        * @param centerX The index of the central column
        * @param centerY The index of the central row
        */
        void setKernelSize(size_t centerX, size_t centerY);

        /**
        * Abstract function for computing the kernel for derived classes to 
        * use.
        */
        virtual void computeKernel() = 0;

        /**
        * Performs convoution multiplication of the kernel and masked pixel
        * matrix around x, y.
        * 
        * Convolution is done by multiplying each kernel entry (row, col) with
        * the corresponding image pixel at (row, col) formed at center (x, y)
        * on the given image.
        * This is done for each channel R, G, B, A
        * 
        * @note Out of bound pixels needed are handled with edge_method
        * @note The resulting color may clip.
        */
        virtual RGBAPixel convolution(const Image& img, unsigned int x, unsigned int y);

        /**
        * Normalized the sum of all weights to 1.
        * 
        * This guarentees no "loss" or "gain" of color.
        * Optional to use. Some convolutions may not use a normalized kernel.
        */
        void normalize();

        Eigen::MatrixXf kernel; /**< The kernel matrix */
    };

}

#endif //_LIBLMTKIMAGE_CONVOLUTION_H_