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
* @file chromakeyer.h
* @author marinarasub
* @date December 2021
* @brief Header file for chroma keyer functor
*/


#ifndef _LIBLMTKIMAGE_CHROMAKEYER_H_
#define _LIBLMTKIMAGE_CHROMAKEYER_H_
#pragma once

#include "imageshader.h"


namespace image {

    /**
    * @class ChromaKeyer "chromakeyer.h"
    * @brief Class for a simple chroma keyer (aka green screen).
    *
    * For every pixel in a given image, the operator sets the alpha to 0 if the
    * color distance is within a defined threshold of the target color (default 
    * 0, which means the colors must be equal)
    */
    class ChromaKeyer : public ImageShader
    {
    public:

        /**
        * The default color distance threshold.
        */
        static constexpr float DEFAULT_TOLERANCE = 0.1;

        /**
        * Creates a chroma keyer functor with default tolerance.
        *
        * Sets the color threshold to default
        * @param target Target color to be removed.
        */
        ChromaKeyer(RGBAPixel target);
        /**
        * Creates a chroma keyer functor with tolerance.
        *
        * @param target Target color to be removed.
        * @param tol Minimum threshold distance from the target color to
        * be removed.
        */
        ChromaKeyer(RGBAPixel target, float tol);

        /**
        * Removes the target color from the image.
        *
        * For each pixel in the image, removes the pixel if it is within threshold
        * of the target color. It removes a color by setting its alpha value to 0.
        * Otherwise, the pixel is left alone.
        *
        * @param img Image to operate chroma keyer on
        */
        virtual void operator()(Image& img) override;

        /**
        * Returns a transparent pixel if the original pixel is within tolerance
        * of target.
        *
        * Does not change the R, G, B channels in case alpha channel is ignored
        * @param img Image to operate chroma keyer on
        * @param x X location of target pixel
        * @param y Y location of target pixel
        * @return Transparent if within threshold, else the original pixel
        */
        virtual RGBAPixel operator()(const Image& img, int x, int y) override;

        // copy chroma keyer
        virtual ChromaKeyer* clone() override;

    private:
        RGBAPixel target; /**< target color defined in RGBA format */
        float threshold = 0; /**< max color distance for which a pixel is removed */
    };

}

#endif // _LIBLMTKIMAGE_CHROMAKEYER_H_