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
* @file imageshader.h
* @author marinarasub
* @date December 2021
* @brief Header file containing base class for image and pixel shaders
*/


#ifndef _LIBLMTKIMAGE_IMAGESHADER_H_
#define _LIBLMTKIMAGE_IMAGESHADER_H_
#pragma once

#include "image.h"
#include "rgbapixel.h"
#include "hslapixel.h"


namespace image {

    /**
    * @class ImageShader "imageshader.h"
    * @brief Abstract class for an image shader
    *
    * An image shader operates on a given image with any possible function(s) on
    * any desired pixel and the image is modified per such function(s).
    */
    class ImageShader
    {
    public:

        /**< Default edge handling method */
        static const EdgeHandlingMethod DEFAULT_EDGE_METHOD
            = EdgeHandlingMethod::EXTEND;

        /**
        * Create an image shader with the default edge handling method.
        */
        ImageShader() : ImageShader(DEFAULT_EDGE_METHOD) {}

        /**
        * Created an image shader with specified edge handling method.
        */
        ImageShader(EdgeHandlingMethod method) : edge_method(method) {}

        /**
        * Virtual destructor for an image shader functor.
        */
        virtual ~ImageShader() {};

        /**
        * Image operator, applies the pixel shader on the whole image.
        * 
        * Can be overriden, but provides basic one-pass shade without extra 
        * memory.
        */
        virtual void operator()(Image& img);

        /**
        * Abstract pixel shader.
        * 
        * Returns a single pixel given a location.
        * @note Sometimes it is useful to sample pixels outside of bounds.
        * Can be overriden do anything you want with the image.
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) = 0;

        // create copy ptr on free store (new)
        virtual ImageShader* clone() = 0;


    protected:

        EdgeHandlingMethod edge_method; /**< Edge handling method 
                                             @see EdgeHandlingMethod */
    };

}

#endif // _LIBLMTKIMAGE_IMAGESHADER_H_