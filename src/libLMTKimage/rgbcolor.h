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
 * @file rgbcolor.h
 * @author marinarasub
 * @date December 2021
 * @brief This file contains useful constants and such for common RGB colors.
 */


#ifndef _LIBLMTKIMAGE_RGBCOLOR_H_
#define _LIBLMTKIMAGE_RGBCOLOR_H_
#pragma once

#include "rgbapixel.h"


namespace image {

    /**
    * @namespace image::rgbcolor
    * @brief Contains common colors as constants for convinience.
    * @see RGBAPixel
    */
    namespace rgbcolor {

        static const RGBAPixel TRANSPARENT(0.0, 0.0, 0.0, 0.0); /**< Transparent */

        static const RGBAPixel WHITE(1.0, 1.0, 1.0, 1.0); /**< White */

        static const RGBAPixel GREY(0.5, 0.5, 0.5, 1.0); /**< Grey, same as Gray */

        static const RGBAPixel GRAY = GREY; /**< Gray, same as Grey */

        static const RGBAPixel BLACK(0.0, 0.0, 0.0, 1.0); /**< Black */

        static const RGBAPixel RED(1.0, 0.0, 0.0, 1.0); /**< Red */

        static const RGBAPixel GREEN(0.0, 1.0, 0.0, 1.0); /**< Green */

        static const RGBAPixel BLUE(0.0, 0.0, 1.0, 1.0); /**< Blue */

        static const RGBAPixel YELLOW(1.0, 1.0, 0.0, 1.0); /**< Yellow */

    }

}

#endif // _LIBLMTKIMAGE_RGBCOLOR_H_