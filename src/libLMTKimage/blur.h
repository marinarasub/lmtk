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
 * @file blur.h
 * @author marinarasub
 * @date December 2021
 * @brief File containing resizable blurs
 */


#ifndef _LIBLMTKIMAGE_BLUR_H_
#define _LIBLMTKIMAGE_BLUR_H_
#pragma once

#include "convolution.h"


namespace image {

    // may not use this class
    class Blur : public ImageConvolution
    {
    public:

        /**
        * Returns (ptr) a new blur of original type scaled blur amount by scalar
        * 
        * @param scalar Blur size multiplier
        */
        virtual Blur* operator*(double scalar) = 0;

        /**
        * Clone the blur, return new-allocated pointer
        */
        virtual Blur* clone() override = 0;

    protected:

        Blur() : ImageConvolution() {}

        Blur(size_t radius) 
            : ImageConvolution(radius) {}

        Blur(size_t radiusX, size_t radiusY) 
            : ImageConvolution(radiusX, radiusY) {}
    };

}

#endif // _LIBLMTKIMAGE_BLUR_H_