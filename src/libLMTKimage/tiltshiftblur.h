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
 * @file tiltshiftblur.h
 * @author marinarasub
 * @date January 2022
 * @brief This file contains a functor for tilt-shift blur
 */

#ifndef _LIBLMTKIMAGE_TILTSHIFTBLUR_H_
#define _LIBLMTKIMAGE_TILTSHIFTBLUR_H_
#pragma once

#include "imageshader.h"
#include "blur.h"


namespace image {

    /**
    * @class TiltShiftBlur "tiltshiftblur.h"
    * @author marinarasub
    * @date February 2022
    * @brief Class for creating a tilt shift blur given a blur technique/method.
    */
    class TiltShiftBlur : public ImageShader
    {

        static const float LINEAR_FADE_SPEED;
        static const float QUADRATIC_FADE_SPEED;
        static const float CUBIC_FADE_SPEED;

    public:

        /**
        * Create a tilt-shift blur shader with blur start locations and a blur
        * method.
        * 
        * @param top Anything above this y will be blurred
        * @param bottom Anything below this y will be blurred
        * @param grad How much to fade the blur by, in pixels
        * @param blur_method The blur shader to use to blur, at max strength 
        * (no fade)
        * @note uses default fade speed quadratic, since blur area scales 
        * quadratically from radius increase.
        */
        TiltShiftBlur(int top, int bottom, float grad, Blur* blur_method);

        /**
        * Create a tilt-shift blur shader with blur start locations and a blur
        * method.
        *
        * @param top Anything above this y will be blurred
        * @param bottom Anything below this y will be blurred
        * @param grad How much to fade the blur by, in pixels
        * @param fade_exp Controls 1/exponent on the fade curve. A higher number
        * is a faster fade.
        * @param blur_method The blur shader to use to blur, at max strength 
        * (no fade)
        */
        TiltShiftBlur(int top, int bottom, float grad, float fade_exp, Blur* blur_method);

        /**
        * / nothing /
        */
        ~TiltShiftBlur();

        /**
        * Apply tilt-shift blur to a given image.
        * 
        * @param img Image to apply tilt-shift blur
        */
        virtual void operator()(Image& img) override;

        /**
        * Return the pixel after applying a tilt-shift blur with creation
        * parameters at x, y.
        * 
        * @param img Image to select pixels from
        * @param x X location of pixel to return
        * @param y Y locaiton of pixel to return
        * @return Tilt-shift blur applied pixel
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y)
            override;

        // copy tilt shift blur, copy blur method as well
        virtual TiltShiftBlur* clone() override;

    private:

        int top_y;
        int bot_y;
        float grad;
        float fade_exp;

        Blur* blur_method; // will call to blur

    };
}

#endif // _LIBLMTKIMAGE_TILTSHIFTBLUR_H_