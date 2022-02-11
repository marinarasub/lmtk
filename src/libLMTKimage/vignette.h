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
 * @file vignette.h
 * @author marinarasub
 * @date December 2021
 * @brief File containing for applying radial vignette to image
 */

#ifndef _LIBLMTKIMAGE_VIGNETTE_H_
#define _LIBLMTKIMAGE_VIGNETTE_H_
#pragma once

#include "imageshader.h"
#include "color.h"
#include "../utils/utilsmath.h"


namespace image {

    /**
    * @class VignetteShader "vignette.h"
    * @author marinarasub
    * @date February 2022
    * @brief Class for applying a vignette to an image
    */
    class VignetteShader : public ImageShader
    {

        /**< The default fade color is black */
        static const RGBAPixel DEFAULT_FADE_COLOR;

    public:

        /**
        * Create a vignette shader with horizontal and vertical radii, and fade
        * amount
        * 
        * @param rX Horizontal radius
        * @param rY Vertical radius
        * @param fade Fade weight. A higher number is a faster fade.
        */
        VignetteShader(float rX, float rY, float fade);

        // TODO make clearer what fade weight is.
        /**
        * Create a vignette shader with horizontal and vertical radii, and fade
        * amount
        *
        * @param rX Horizontal radius
        * @param rY Vertical radius
        * @param fade Fade weight. A higher number is a faster fade.
        * @param color Fade color
        */
        VignetteShader(float rX, float rY, float fade, RGBAPixel color);

        /**
        * Apply vignette to given image
        * 
        * @param img Image to apply vignette on
        */
        virtual void operator()(Image& img) override;

        /**
        * Return the color at x, y of the given image with a vignette filter.
        * 
        * @param img Image to apply vignette from
        * @param x X location from image
        * @param y Y location from image
        * @return Vignetted pixel at x, y from image
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) override;

        // copy vignette shader
        virtual VignetteShader* clone() override;

    private:

        float radiusX;
        float radiusY;
        float gradient;

        RGBAPixel fade_color;
    };
}

#endif // _LIBLMTKIMAGE_VIGNETTE_H_
