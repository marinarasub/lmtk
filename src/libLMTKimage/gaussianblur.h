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
 * @file gaussianblur.h
 * @author marinarasub
 * @date December 2021
 * @brief Header file for gaussian blur shader
 */


#ifndef _LIBLMTKIMAGE_GAUSSIANBLUR_H_
#define _LIBLMTKIMAGE_GAUSSIANBLUR_H_
#pragma once

#include <math.h>
#include "convolution.h"
#include "../utils/utilsmath.h"


namespace image {

    /**
    * Helper function for computing gaussian() from given z-score
    * 
    * @param zscore Z-score, or standard deviations from mean
    * @return gaussian function result
    */
    static float sigmaTolerance(float zscore);

    /**
    * @class GaussianBlur "gaussianblur.h"
    * @brief Class for gaussian blur kernel filtering of an image
    * 
    * Blurs the image, taking neigboring pixel weighted according to the 
    * gaussian/normal distribution function. The result is a smooth, but rather
    * boring looking blur.
    * @see utils::math::gaussian()
    */
    class GaussianBlur : public ImageConvolution
    {
    public:

        /**
        * Creates a gaussian blur with a given standard deviation.
        * 
        * Standard deviation is in pixels. May be fractional.
        * @param stdev Standard deviation
        */
        GaussianBlur(float stdev);

        /**
        * Creates gaussian blur with horizontal and vertical standard deviation.
        *
        * Standard deviation is in pixels. May be fractional.
        * @param stdevX Horizontal standard deviation
        * @param stdevY Vertial standard deviation
        */
        GaussianBlur(float stdevX, float stdevY);

        /**
        * Creates gaussian blur with standard deviations and tolerances.
        *
        * Standard deviation is in pixels. May be fractional.
        * Tolerance refers to the value for which any weights smaller than it
        * will not be included in the kernel. A low tolerance will be more 
        * accurate, but a cost of a larger kernel (with diminishing return)
        * @note Default tolerance is 3 standard deviations (~99.7%)
        * @param stdevX Horizontal standard deviation
        * @param stdevY Vertial standard deviation
        * @param toleranceX Tolerance for kernel columns
        * @param toleranceY Tolerance for kernel rows
        */
        GaussianBlur(float stdevX, float stdevY, float toleranceX, float toleranceY);

    private:

        /**
        * Computes the kernel according to the gaussian function.
        * 
        * @see utils::math::gaussian2d()
        */
        virtual void computeKernel() override;

        float sigmaX; /**< Horizontal standard deviation */
        float sigmaY; /**< Vertical standard deviation */

    };


    /**
    * @class GaussianBlurHorizontal "gaussianblur.h"
    * @brief Class for seperable horizontal component of gaussian blur
    *
    * Blurs the image according to the gaussian horizontally
    * @see GaussianBlur
    */
    class GaussianBlurHorizontal : public ImageConvolution
    {
    public:

        /**
        * Creates a horizontal gaussian blur with a standard deviation.
        *
        * Standard deviation is in pixels. May be fractional.
        * @param stdev Horizontal standard deviation
        */
        GaussianBlurHorizontal(float stdev);

        /**
        * Create gaussian blur with horizontal standard deviation and tolerance.
        *
        * Standard deviation is in pixels. May be fractional.
        * Tolerance refers to the value for which any weights smaller than it
        * will not be included in the kernel.
        * @param stdev Horizontal standard deviation
        * @param tol Tolerance for kernel weights
        */
        GaussianBlurHorizontal(float stdev, float tol);

    private:

        /**
        * Computes the kernel according to the gaussian function.
        *
        * @see utils::math::gaussian()
        */
        virtual void computeKernel() override;

        float sigma; /**< Horizontal standard deviation */

    };


    /**
    * @class GaussianBlurVertical "gaussianblur.h"
    * @brief Class for seperable vertical component of gaussian blur
    *
    * Blurs the image according to the gaussian vertically
    * @see GaussianBlur
    */
    class GaussianBlurVertical : public ImageConvolution
    {
    public:

        /**
        * Creates vertical gaussian blur with a standard deviation.
        *
        * Standard deviation is in pixels. May be fractional.
        * @param stdev Vertical standard deviation
        */
        GaussianBlurVertical(float stdev);

        /**
        * Create gaussian blur with vertical standard deviation and tolerance.
        *
        * Standard deviation is in pixels. May be fractional.
        * Tolerance refers to the value for which any weights smaller than it
        * will not be included in the kernel.
        * @param stdev Vertical standard deviation
        * @param tol Tolerance for kernel weights
        */
        GaussianBlurVertical(float stdev, float tol);

    private:

        /**
        * Computes the kernel according to the gaussian function.
        *
        * @see utils::math::gaussian()
        */
        virtual void computeKernel() override;

        float sigma; /**< Vertical standard deviation */

    };


}

#endif // _LIBLMTKIMAGE_GAUSSIANBLUR_H_

