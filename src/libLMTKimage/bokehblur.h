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
 * @file bokehblur.h
 * @author marinarasub
 * @date January 2022
 * @brief This file contains a functor for bokeh blur
 */

#ifndef _LIBLMTKIMAGE_BOKEHBLUR_H_
#define _LIBLMTKIMAGE_BOKEHBLUR_H_
#pragma once

#include "blur.h"
#include "../utils/utilsmath.h"


namespace image {

    /**
    * @class BokehBlur "bokehblur.h"
    * @brief Class for a bokeh/lens blur using a disk/circular convolution
    * 
    * @see ImageConvolution
    */
    class BokehBlur : public Blur
    {
    public:

        // Note: may want to correct lighting / highlights for artistic effect

        /**
        * Constructs a bokeh blur functor with blur radius.
        * 
        * @param radius Radius of blur
        */
        BokehBlur(float radius);

        /**
        * Constructs a bokeh blur functor with horizontal and vertial blur radius.
        *
        * @param radiusX Horizontal radius of blur
        * @param radiusY Vertical radius of blur
        */
        BokehBlur(float radiusX, float radiusY);

        // scale bokeh
        virtual BokehBlur* operator*(double scalar) override;

        // clone bokeh
        virtual BokehBlur* clone() override;

    private:

        /**
        * Computes a circular kernel using radii x, y.
        * 
        * The edges are antialiased.
        * @see ImageConvolution::computeKernel()
        */
        virtual void computeKernel() override;

        float radiusX; /**< Horizontal radius */
        float radiusY; /**< Vertical radius */
    };

}

#endif // _LIBLMTKIMAGE_BOKEHBLUR_H_