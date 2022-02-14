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
 * @file grayscale.h
 * @author marinarasub
 * @date December 2021
 * @brief Header file for a converting an image to a grayscale image.
 */


#ifndef _LIBLMTKIMAGE_GRAYSCALE_H_
#define _LIBLMTKIMAGE_GRAYSCALE_H_
#pragma once

#include "imageshader.h"


namespace image {

    /**
    * @class GrayScaleShader "grayscale.h"
    * @brief Class for a converting any image to a grayscale version
    *
    * In a grayscale image each pixel is a shade of gray, with only varying 
    * intensity.
    * Gray is defined where the RGB components all have the same value.
    * This means if desired, only one color channel would be required.
    */
    class GrayScaleShader : public ImageShader
    {
    public:

        /**
        * Grayscale each pixel in the image.
        * 
        * @param img Image to grayscale
        */
        virtual void operator()(Image& img) override;

        /**
        * Grayscale a pixel.
        * 
        * @param img Image to select pixel from
        * @param x X location of target pixel
        * @param y Y location of target pixel
        * @return Grayscaled pixel
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) override;

        // copy grayscale
        virtual GrayScaleShader* clone() override;


    private:

        /**
        * Makes a pixel grey.
        *
        * The grey intensity is determined by the average of the R, G, B values.
        * @param p Pixel to grayscale
        * @return Grayscaled pixel
        */
        RGBAPixel greyScale(RGBAPixel p);
    };

}

#endif // _LIBLMTKIMAGE_GRAYSCALE_H_