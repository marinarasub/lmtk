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
* @file colorinvert.h
* @author marinarasub
* @date December 2021
* @brief Header file for color invert functor
*/


#ifndef _LIBLMTKIMAGE_COLORINVERT_H_
#define _LIBLMTKIMAGE_COLORINVERT_H_
#pragma once

#include "imageshader.h"


namespace image {

    /**
    * @class ColorInvertShader "colorinvert.h"
    * @brief Class for a color inversion
    *
    * For every pixel in a given image, the R, G, B channels are inverted and the
    * alpha is left as is.
    * @see ImageShader
    */
    class ColorInvertShader : public ImageShader
    {
    public:

        /**
        * Creates a color inversion image functor.
        *
        * Inverts every pixel in the image by calling invert()
        * @see invert()
        * @param img Image to invert
        */
        virtual void operator()(Image& img) override;

        /**
        * Creates a color inversion pixel functor.
        *
        * Inverts every pixel in the image by calling invert()
        * @see invert()
        * @param img Image to sample from
        * @param x X location of target
        * @param y Y location of target
        */
        virtual RGBAPixel operator()(const Image& img, size_t x, size_t y) override;

    private:
        /**
        * Inverts the pixel's color.
        *
        * Inversion means each channel R, G, B value is set to MAX - CURRENT
        * @param p Pixel to invert
        */
        RGBAPixel invert(RGBAPixel p);
    };

}

#endif // _LIBLMTKIMAGE_COLORINVERT_H_

