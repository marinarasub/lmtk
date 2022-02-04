/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in the utils library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file utils.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing various utility functions
 */

#ifndef _UTILS_UTILS_H_
#define _UTILS_UTILS_H_
#pragma once

#include <limits>
#include <cstdint>
#include <string>

namespace utils
{
    /**
    * Returns the maximum value for an unsigned int of a given bit depth.
    *
    * The maximum value is where $bit_depth$ number of bits are set.
    * @param bit_depth The bit depth, in bits
    * @return The maximum unsigned integer value of a bit depth
    * @note is the bit_depth given is > 32, use UINT32_MAX
    */
    uint32_t uint_max_val(uint8_t bit_depth);


    /**
    * Determines the tightest power of 2 that is equal or greater than a number.
    * 
    * @param val Number to check
    */
    uint64_t uint64_next_pwr2(uint64_t val);

    // WIP, given number of bytes return string rep. in readeable format 
    // (kb, mb, gb etc)
    std::string get_size_string(size_t num_bytes);

}

#endif // _UTILS_UTILS_H_
