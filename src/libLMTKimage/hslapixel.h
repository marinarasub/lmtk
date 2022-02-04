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
 * @file hslapixel.h
 * @author marinarasub
 * @date January 2022
 * @brief This file contains the class for representing color using the HSLA
 * color model.
 */


#ifndef _LIBLMTKIMAGE_HSLAPIXEL_H_
#define _LIBLMTKIMAGE_HSLAPIXEL_H_
#pragma once

#include <iostream>
#include <string>
#include "color.h"
#include "rgbapixel.h"


namespace image {

    class RGBAPixel;


    /**
    * @class HSLAPixel "hslapixel.h"
    * @brief Class for representing a pixel's color using the HSL color model
    * 
    * HSL: Hue, Saturation and Luminance.
    * H is the hue, which can be represented by an angle. The resulting "color 
    * wheel" is a rainbow spectrum. This implementation uses degrees [0, 360).
    * S is the saturation, which is the "amount of color" or vibrance of the
    * color. A lower value means grey, and a higher value is very bright.
    * L is the luminance, which is the intensity of the light. A lower value is
    * close to black, a higher value is close to white.
    * In addition, there is an alpha layer which is the opacity of the image and
    * can be used to overlay different images when suppported.
    * @see color
    */
    class HSLAPixel
    {

    public:

        // TODO avg functions

        /**
        * Creates default HSLA Pixel.
        * 
        * Default value is 0 for each channel
        */
        HSLAPixel();

        /**
        * Creates HSLA Pixel given hue, saturation, lumimance, and alpha
        * 
        * Clamps the values.
        * @see clampHSLA()
        * @param h Hue in degrees (can be negative)
        * @param s Saturation [0, 1]
        * @param l Luminance [0, 1]
        * @param a Alpha [0, 1]
        */
        HSLAPixel(float h, float s, float l, float a);

        /**
        * Converts RGBA Pixel to HSLA.
        * 
        * @param rgb RGBA Pixel
        */
        HSLAPixel(const RGBAPixel& rgb);

        /**
        * Assignment operator: copies other's h, s, l, a values to *this
        * 
        * @param other HSLA Pixel to copy
        */
        void operator=(const HSLAPixel& other);

        /**
        * Equality operator: checks if two HSLA Pixels are equal
        * 
        * Each channel H, S, L, A must be equal.
        * @param other Other pixel to check
        * @return True if the two are equal, false otherwise
        */
        bool operator==(const HSLAPixel& other) const;

        /**
        * Inequality operator: check if two HSLA Pixels are not equal
        * 
        * @see operator==()
        * @param other Other pixel to check
        * @return True if the two are not equal, false otherwise
        */
        bool operator!=(const HSLAPixel& other) const;

        /**
        * Sets the H, S, L values.
        * 
        * Will clamp values
        * @see HSLAClamp()
        * @param h Hue value
        * @param s Saturation value
        * @param l Luminance value
        */
        void set(float h, float s, float l);

        /**
        * Sets the H, S, L and A values.
        *
        * Will clamp values
        * @see HSLAClamp()
        * @param h Hue value
        * @param s Saturation value
        * @param l Luminance value
        * @param a Alpha
        */
        void set(float h, float s, float l, float a);

        /**
        * Sets all channel values to that of another pixel.
        *
        * Equivalent to operator=
        * @param other Color to set to
        */
        void set(const HSLAPixel& other);

        /**
        * Sets HSL values converted from RGB, and alpha.
        *
        * @see color
        * @param other Color to set to
        */
        void set(const RGBAPixel& other);

        /**
        * Set the alpha value
        * 
        * @param a Alpha
        */
        void setAlpha(float a);

        /**
        * Sets the transparency.
        *
        * Transparency is 1.0 - alpha
        * @param a Alpha value
        */
        void setTransparency(float transparency);

        // !!! This function is subject to change.
        /**
        * Returns a string representation of the HSLA.
        *
        * @return The string representation
        */
        std::string to_string() const; // todo stream operator instead??

        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float h; /**< Represents the amount of hue in degrees [0, 360) */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float s; /**< Represents the amount of saturation [0, 1] */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float l; /**< Represents the amount of lightness [0, 1] */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float a; /**< Represents the alpha [0, 1] */

    private:

        /**
        * Clamps HSLA channels as specified below
        *
        * @note NaN is handled according to fmin, fmax specification of choosing
        * the other argument, so the final result will be 1.0
        */
        void clampHSLA();


    };

    /**
    * Add string representation of pixel to stream
    *
    * @param out Output stream
    * @param pixel Pixel to output to stream
    */
    std::ostream& operator<<(std::ostream& out, const HSLAPixel& pixel);
}

#endif // _LIBLMTKIMAGE_HSLAPIXEL_H_