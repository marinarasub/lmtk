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
 * @file hslcolor.h
 * @author marinarasub
 * @date January 2022
 * @brief This file contains useful constants and such for common HSL colors.
 */


#ifndef _LIBLMTKIMAGE_HSLCOLOR_H_
#define _LIBLMTKIMAGE_HSLCOLOR_H_
#pragma once

#include "hslapixel.h"


namespace image {

    /**
    * @namespace image::hslcolor
    * @brief Contains common colors as constants for convinience.
    * @see HSLAPixel
    */
    namespace hslcolor {

        static const HSLAPixel TRANSPARENT(0.0, 0.0, 0.0, 0.0); /**< Transparent */

        // TODO add more colors
    }

}

#endif // _LIBLMTKIMAGE_HSLCOLOR_H_