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
 * @file rotate.h
 * @author marinarasub
 * @date December 2021
 * @brief File for rotating an image
 */

#ifndef _LIBLMTKIMAGE_ROTATE_H_
#define _LIBLMTKIMAGE_ROTATE_H_
#pragma once

#include <cmath>
#include <Eigen/Dense>
#include "imageshader.h"
#include "../utils/utilsmath.h"


namespace image {
    
    /**
    * @class ImageRotate "imagerotate.h"
    * @author marinarasub
    * @date February 2022
    * @brief Class for rotating an image on 2D plane 
    * (clockwise/counterclockwise)
    */
    class ImageRotate : public ImageShader
    {
    public:

        // TODO choose resample method
        // TODO antialias edges
        /**
        * Create an image rotation functor
        * 
        * @param deg Degrees to rotate, counterclockwise
        */
        ImageRotate(float deg);

        /**
        * Rotates the given image and places in inside bounding box.
        * 
        * @param img Image to rotate
        */
        virtual void operator()(Image& img) override;

        /**
        * Return the pixel at x, y, post rotation.
        * 
        * @param img Original image
        * @param x X location of transformed pixel
        * @param y Y location of transformed pixel
        * @return The rotated pixel, transparent if none.
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) override;

        // copy rotation shader
        virtual ImageRotate* clone() override;

    private:

        /**
        * Helper function for determining size of bouding rectangle for a
        * rotated image.
        */
        std::pair<int, int> bouding_rect(int x, int y);

        float radians;

        Eigen::Matrix2f rot_matrix;
    };

}

#endif // _LIBLMTKIMAGE_ROTATE_H_

