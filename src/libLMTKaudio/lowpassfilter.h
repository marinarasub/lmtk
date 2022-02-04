/***************************************************************************//**
 * Copyright (c) 2022 marinarasub
 *
 * LMTK / Light Multimedia ToolKit
 *
 * This file is included in libLMTKaudio, the audio library for LMTK
 * LMTK and its subprojects are available under the MIT license.
 *
 ******************************************************************************/

 /**
 * @file lowpassfilter.h
 * @author marinarasub
 * @date January 2022
 * @brief Contians handy constants and conversions from musical notes (letters)
 * to frequencies.
 */

// !!! NOT YET IMPLEMENTED !!! //
#ifndef _AUDIO_LOWPASSFILTER_H_
#define _AUDIO_LOWPASSFILTER_H_
#pragma once

#include "audiofilter.h"
#include <Eigen/Dense>


namespace audio {

    class LowPassFilter : public AudioFilter
    {
    public:
        LowPassFilter(float cutoff) : cutoff_freq(cutoff) {};

        void operator()(AudioTrack& track);

    private:
        float cutoff_freq;
    };

}

#endif // _AUDIO_LOWPASSFILTER_H_

