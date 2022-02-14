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
 * @file boxblur.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing classes for box blur
 * 
 * Contains both full version and seperable versions (horizontal/vertical) 
 */


#ifndef _LIBLMTKIMAGE_BOXBLUR_H_
#define _LIBLMTKIMAGE_BOXBLUR_H_
#pragma once

#include "blur.h"

namespace image {

    /**< Default box blur radius for 3x3 */
    static const size_t DEFAULT_BOXBLUR_RADIUS = 1; // 3x3

    /**
    * @class BoxBlur "boxblur.h"
    * @brief Class for box blur
    * 
    * A box blur convolution is all 1's, smoothing the image with equally 
    * weighted surrounding pixels.
    * Repeated iterations / multiple passes approximates the Gaussian Blur.
    * @see GaussianBlur
    */
    class BoxBlur : public Blur
    {
    public:

        /**
        * Creates a box blur with a default 3x3 convolution
        */
        BoxBlur();

        /**
        * Creates a box blur given radius.
        * 
        * @param radius The matrix radius
        * @note "radius" loosely refers to how many pixels the matrix extends 
        * from the center horizontally and vertically
        * @see ImageConvolution()
        */
        BoxBlur(size_t radius);

        /**
        * Creates a box blur given horizontal and vertial radius.
        *
        * @param radiusX The horizontal matrix radius
        * @param radiusY The vertical matrix radius
        * @note "radius" loosely refers to how many pixels the matrix extends
        * from the center horizontally and vertically
        * @see ImageConvolution()
        */
        BoxBlur(size_t radiusX, size_t radiusY);

        // scale box blur
        virtual BoxBlur* operator*(double scalar) override;

        // copy box blur
        virtual BoxBlur* clone() override;

    private:

        /**
        * Sets the kernel to all 1, normalized.
        */
        virtual void computeKernel() override;

        float radiusX;
        float radiusY;
;
    };


    /**
     * @class BoxBlurHorizontal "boxblur.h"
     * @brief Class for box blur's seperable horizontal component
     *
     * The horizontal convolution of box blur, which is a seperable kernel and
     * may be done with a horizontal pass followed by a vertical pass (or vice 
     * versa), reducing time complexity from O(n * m) to O(n + m)
     * @see BoxBlur
     * @see BoxBlurVertical
     */
    class BoxBlurHorizontal : public Blur
    {
    public:

        /**
        * Creates a box blur with default 3x1 convolution
        */
        BoxBlurHorizontal();

        /**
        * Creates a box blur with a mx1 convolution
        * 
        * @param radius Horizontal radius
        */
        BoxBlurHorizontal(size_t radius);

        // scale box blur
        virtual BoxBlurHorizontal* operator*(double scalar) override;

        virtual BoxBlurHorizontal* clone() override;

    private:

        /**
        * Sets the kernel to all 1, normalized.
        */
        virtual void computeKernel() override;

        float hradius;


    };


    /**
     * @class BoxBlurVertical "boxblur.h"
     * @brief Class for box blur's seperable vertical component
     *
     * The vertical convolution of box blur, which is a seperable kernel and
     * may be done with a horizontal pass followed by a vertical pass (or vice 
     * versa), reducing time complexity from O(n * m) to O(n + m)
     * @see BoxBlur
     * @see BoxBlurHorizontal
     */
    class BoxBlurVertical : public Blur
    {
    public:

        /**
        * Creates a box blur with default 1x3 convolution
        */
        BoxBlurVertical();

        /**
        * Creates a box blur with a 1xn convolution
        *
        * @param radius Vertical radius
        */
        BoxBlurVertical(size_t radius);

        // scale box blur
        virtual BoxBlurVertical* operator*(double scalar) override;

        virtual BoxBlurVertical* clone() override;

    private:

        /**
        * Sets the kernel to all 1, normalized.
        */
        virtual void computeKernel() override;

        float vradius;

    };

}

#endif // _LIBLMTKIMAGE_BOXBLUR_H_