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
 * @file huesatlum.h
 * @author marinarasub
 * @date January 2022
 * @brief Header file for a adjusting HSL of an image
 */

#ifndef _LIBLMTKIMAGE_HUESATLUM_H_
#define _LIBLMTKIMAGE_HUESATLUM_H_
#pragma once

#include "imageshader.h"


namespace image {

    /**
    * @class HueSatLumAdjust "huesatlum.h"
    * @brief Class for adjustin the hue, saturation, and luminance of an image
    * @see HSLAPixel
    */
    class HueSatLumAdjust : public ImageShader
    {
    public:

        /**
        * Creates a HSL Adjust functor with hue shift, saturation and luminance 
        * multiplier.
        * 
        * @param hue Hue shift in degrees
        * @param sat Saturation multiplier
        * @param lum Luminance multiplier
        */
        HueSatLumAdjust(float hue, float sat, float lum);

        /**
        * Adjust the HSL of an image
        *
        * @param img Image to adjust
        */
        virtual void operator()(Image& img) override;

        /**
        * Return the HSL adjusted color
        *
        * @param img Image to select pixel from
        * @param x X location of target pixel
        * @param y Y location of target pixel
        * @return HSL Adjusted color
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) override;

        // copy hsl shader
        virtual HueSatLumAdjust* clone() override;

    private:

        float hue_shift; /**< The hue shift in degrees. Can be negative */
        float sat_multiplier; /**< Saturation scalar */
        float lum_multiplier; /**< Luminance scalar */
    };

}

#endif // _LIBLMTKIMAGE_HUESATLUM_H_