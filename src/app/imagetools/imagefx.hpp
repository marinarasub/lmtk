/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in the LMTKimage app component of LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file imagefx.hpp
 * @author marinarasub
 * @date January 2022
 * @brief Header file for string arg wrappers for LMTK image shaders library
 *
 * @ref imageshader.h
 */

#ifndef _LMTKIMAGE_IMAGEFX_H_
#define _LMTKIMAGE_IMAGEFX_H_
#pragma once


#include <string>
#include <vector>
#include <unordered_map> // TODO ordered map by alphabetical??? or nah
#include <functional>
#include "../../libLMTKimage/pluginchain.h"
#include "../../libLMTKimage/filters.h"


namespace lmtkimage
{
	using namespace image;

    // TODO make except. use map usage field
    // TODO count passes since removed from image shaders TODO!!!!!!
    // TODO return multiple

    std::vector<ImageShader*> make_bokeh_blur(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_box_blur(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_fast_blur(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_chroma_keyer(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_color_invert(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_gaussian_blur(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_grayscale(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_hsl_adjust(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_image_sharpen(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_tilt_shift(size_t passes, std::vector<std::string> args);

    std::vector<ImageShader*> make_vignette(size_t passes, std::vector<std::string> args);

    struct fx_info
    {
        std::function<std::vector<ImageShader*>(size_t passes, std::vector<std::string>)> function;
        std::string description;
        std::string usage;
    };

    // help msg for usage of fx
    std::string help_fx();

    // returns null if not found
    std::vector<ImageShader*> get_effects(std::string effect, size_t passes, std::vector<std::string> args);


}


#endif // _LMTKIMAGE_IMAGEFX_H_