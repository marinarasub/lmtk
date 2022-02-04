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
 * @file color.h
 * @author marinarasub
 * @date January 2022
 * @brief This file contains functions for representing & converting color types
 */


#ifndef _LIBLMTKIMAGE_COLOR_H_
#define _LIBLMTKIMAGE_COLOR_H_
#pragma once

#include <math.h>

/**
* @namespace color
* @brief Contains color representations, functions and conversion between them
*/
namespace color {

    // RGB color model
    // see https://en.wikipedia.org/wiki/RGB_color_model
    typedef struct {
        double r, g, b; // [0, 1]
    } rgb_color;

    // HSL color model
    // see https://en.wikipedia.org/wiki/HSL_and_HSV
    typedef struct {
        double h;  // degrees, [0, 360)
        double s;  // [0, 1]
        double l;  // [0, 1]
    } hsl_color;

    // convert explicit rgb to hsl
    hsl_color rgb_to_hsl(double r, double g, double b);

    // convert rgb struct to rsl
    hsl_color rgb_to_hsl(const rgb_color& clr);

    // convert explicit hsl to rgb
    rgb_color hsl_to_rgb(double h, double s, double l);

    // convert hsl struct to rgb
    rgb_color hsl_to_rgb(const hsl_color& clr);

}

#endif //_LIBLMTKIMAGE_COLOR_H_