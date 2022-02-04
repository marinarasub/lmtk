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
* @file rgbapixel.h
* @author marinarasub
* @date December 2021
* @brief This file contains the class for representing color using the RGBA 
* color model.
*/


#ifndef _LIBLMTKIMAGE_RGBAPIXEL_H_
#define _LIBLMTKIMAGE_RGBAPIXEL_H_
#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <math.h>
#include "color.h"
#include "hslapixel.h"
#include "../utils/utils.h"
#include "../utils/utilsmath.h"


namespace image {

    class HSLAPixel;


    // TODO overload addidion/multiplication for colors
    /**
    * @class RGBAPixel rgbapixel.h
    * @brief Represents pixels with color channels red, green, blue and alpha
    *
    * The RGBA color model is an additive color model, where red, green and blue
    * are the primary colors which can be combined to create a wide variety of
    * other colors. White is created when each of the three colors are at maximum
    * intensity, and black is when all three colors have 0 intensity.
    * An additonal channel, alpha represents the opacity of the color which allows
    * the color to be blended with another (known as alpha blending) to create
    * a transparency effect.
    * @see color
    */
    class RGBAPixel
    {

        //typedef char byte_t;

    public:

        /**
        * Computes average RGBA values from 2 pixels.
        *
        * @param p1 First pixel
        * @param p2 Second Pixel
        */
        static RGBAPixel average(RGBAPixel p1, RGBAPixel p2);

        /**
        * Computes average RGBA values from n pixels.
        *
        * @param pixels Pixels to average
        * @param count Number of pixels in array
        */
        static RGBAPixel naverage(RGBAPixel pixels[], size_t count);

        /**
        * Computes weighted average RGBA values from 2 pixels.
        *
        * @param p1 First pixel
        * @param p2 Second Pixel
        * @param w1 Weight for p1
        * @param w2 Weight for p2
        */
        static RGBAPixel weighted_average(RGBAPixel p1, RGBAPixel p2, float w1, float w2);

        /**
        * Computes weighted average RGBA values from n pixels.
        *
        * @param pixels Pixels to average
        * @param weights Weights corresponding to pixel[i]
        * @param count Number of pixels in array
        */
        static RGBAPixel weighted_naverage(RGBAPixel pixels[], float weights[], size_t count);


        /**
        * Constructs a default RGBA Pixel.
        *
        * The default is 0 for each channel.
        */
        RGBAPixel();

        /**
        * Constructs a RGBA pixels given float values for each channel.
        *
        * Sets the alpha to 1.0
        * Each channel is restricted to [0, 1]
        * @see clampRGBA()
        * @param r Red value
        * @param g Green value
        * @param b Blue value
        */
        RGBAPixel(float r, float g, float b);

        /**
        * Constructs a RGBA pixels given float values for each channel.
        *
        * Each channel is restricted to [0, 1]
        * @see clampRGBA()
        * @param r Red value
        * @param g Green value
        * @param b Blue value
        * @param a Alpha value
        */
        RGBAPixel(float r, float g, float b, float a);


        /**
        * Constructs a RGBA pixel given unsigned integer values.
        *
        * RGBA is traditonally defined with an unsigned integer [0, 255] with 8 bit
        * channels, but can accept other bit depths as well.
        * @note the maximum bit depth accepted is 32 (integer/dword)
        * @param r Red value
        * @param g Green value
        * @param b Blue value
        * @param a Alpha value
        * @param bit_depth Bit depth of all the channels
        * @note All channels are assumed to have the same bit depth
        */
        RGBAPixel(
            uint32_t r,
            uint32_t g,
            uint32_t b,
            uint32_t a,
            uint8_t bit_depth
        );


        /**
        * Converts a HSLA Pixel to a RGBA Pixel
        * 
        * @see color
        * @param hsl HSLA Pixel to convert
        */
        RGBAPixel(const HSLAPixel& hsl);

        /**
        * Assignment operator: sets the current RGBA to the other pixel's values.
        *
        * @param other RGBA Pixel to copy
        */
        void operator=(const RGBAPixel& other);

        /**
        * Equality operator: returns true if two colors are equal.
        *
        * Each channel must have the same value, including alpha
        * @param other Other RGBA Pixel to be checked
        * @return True if the colors are equal, false otherwise
        */
        bool operator==(const RGBAPixel& other) const;

        /**
        * Equality operator: returns true if two colors are NOT equal.
        *
        * @see operator==()
        * @param other Other RGBA Pixel to be checked
        * @return True if the colors are not equal, false if they are equal
        */
        bool operator!=(const RGBAPixel& other) const;

        /**
        * Sets the color channels values, RGB.
        *
        * Using this function will also clamp the values if not [0, 1].
        * @see clamp()
        * @param r Red value
        * @param g Green value
        * @param b Blue value
        */
        void set(float r, float g, float b);

        /**
        * Sets all channel values, RGBA.
        *
        * Using this function will also clamp the values if not [0, 1].
        * @see clamp()
        * @param r Red value
        * @param g Green value
        * @param b Blue value
        * @param a Alpha value
        */
        void set(float r, float g, float b, float a);

        /**
        * Sets all channel values to that of another pixel.
        *
        * Equivalent to operator=
        * @param other Color to set to
        */
        void set(const RGBAPixel& other);

        /**
        * Sets the RGB values converted from a HSL, and alpha.
        * 
        * @see color
        */
        void set(const HSLAPixel& other);

        /**
        * Sets the alpha value.
        *
        * @param a Alpha value
        */
        void setAlpha(float a);

        /**
        * Sets the transparency.
        *
        * Transparency is 1.0 - alpha
        * @param a Alpha value
        */
        void setTransparency(float transparency);

        // TODO conversion to HSLA/HSV/CMYK
        // TODO conversion to rgb8, rgb16 etc or store as rgb8 to save memory
        // 

        // compares within float tolerance, unlike operator==
        //bool equals(const RGBAPixel& other);

        /**
        * Returns the euclidian distance between two colors.
        *
        * The eulician distance is the pythagorean sum of the three colored channels
        * (not including alpha)\n
        * dist = sqrt(dRED^2 + dGREEN^2 + dBLUE^2)
        * @note The max distance is therefore sqrt(3)
        * @param other Pixel to compare to
        * @return Distance between the colors
        */
        float dist(const RGBAPixel& other) const;

        // !!! This function is subject to change.
        /**
        * Returns a string representation of the RGBA.
        *
        * @return The string representation
        */
        std::string to_string() const; // todo stream operator instead??

        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float r; /**< Represents the amount of red [0, 1] */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float g; /**< Represents the amount of green [0, 1] */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float b; /**< Represents the amount of blue [0, 1] */
        /** @warning Modifying this directly does not clamp the value. Not
        recommended. */
        float a; /**< Represents the alpha [0, 1] */

    private:
        /**
        * Clamps RGBA channels to [0, 1]
        *
        * @note NaN is handled according to fmin, fmax specification of choosing
        * the other argument, so the final result will be 1.0
        */
        void clampRGBA();

    };

    /**
    * Add string representation of pixel to stream
    * 
    * @param out Output stream
    * @param pixel Pixel to output to stream
    */
    std::ostream& operator<<(std::ostream& out, const RGBAPixel& pixel);

}

#endif // _LIBLMTKIMAGE_RGBAPIXEL_H_