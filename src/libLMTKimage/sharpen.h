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
 * @file sharpen.h
 * @author marinarasub
 * @date January 2022
 * @brief Class for sharpening an image
 */


#ifndef _LIBLMTKIMAGE_SHARPEN_H_
#define _LIBLMTKIMAGE_SHARPEN_H_
#pragma once

#include "convolution.h"

namespace image {

    /**
    * @class ImageSharpen "sharpen.h"
    * @brief class for sharpening an image
    * 
    * Image sharpening is done by emphasizing color differences (edges)
    * This implementation uses a lapacian filter + identity
    */
    class ImageSharpen : public ImageConvolution
    {
    public:

        // sharpen uses 1x1
        static const size_t SHARP_CENTER = 1; 

        /**
        * Create a sharpening functor with default sharpnening amount
        */
        ImageSharpen();

        /**
        * Create a sharpening functor with sharpening amount
        * 
        * @param amt Amount to sharpen
        */
        ImageSharpen(float amt);


    private:

        /**
        * Computes the kernel using laplcian filter plus identity
        */
        virtual void computeKernel() override;

        float amount; /**< Amount to sharpen. Negative values on lapacian */
    };
}

#endif // _LIBLMTKIMAGE_SHARPEN_H_