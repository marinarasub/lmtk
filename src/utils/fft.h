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
 * @file fft.h
 * @author marinarasub
 * @date January 2022
 * @brief Utility class for fourier transform
 */

// !!! TODO WIP !!! //
#ifndef _UTILS_FFT_H_
#define _UTILS_FFT_H_
#pragma once

#include <stdlib.h>
#include <vector>
#include "utils.h"
#include "utilsmath.h"


namespace utils {

    namespace fft {

        std::vector<math::complex>* dft(std::vector<float> &input);

        std::vector<float>* idft(std::vector<math::complex> &coeffs);

        std::vector<math::complex>* fft(std::vector<float>& input);

        std::vector<float>* ifft(std::vector<math::complex>& coeffs);

        std::vector<float>* power_spec(std::vector<math::complex>& input);

        math::complex eitheta(double theta); // e^itheta
        math::complex cis(double theta); // e^itheta
        math::complex eitheta_inv(double theta); // e^itheta
        math::complex cis_inv(double theta); // e^itheta
    }
}

#endif // _UTILS_FFT_H_
