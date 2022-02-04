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
 * @file wavegenerator.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains abstract class for wave singal generation
 */

#ifndef _LIBLMTKAUDIO_WAVEGENERATOR_H_
#define _LIBLMTKAUDIO_WAVEGENERATOR_H_
#pragma once

#include "audiofilter.h"
#include "../utils/utilsmath.h"


namespace audio {

    constexpr double PI = utils::math::PI;

    /**
    * @class WaveGenerator "wavegenerator.h"
    * @brief Abstract wave generator class
    * 
    * Waves generated will be discrete and applied to an audio track
    * @see AudioTrack
    */
    class WaveGenerator : public AudioFilter
    {
    public:
        
        /**
        * Virtual destructor.
        */
        virtual ~WaveGenerator() {};

        /**
        * Abstract function for wave generator.
        * 
        * @param track Audio track to generate over
        */
        virtual void operator()(AudioTrack& track) = 0;

    protected:

        /**
        * Creates a wave given frequencies, amplitude and offset.
        * 
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        * @param offset Offset from 0
        */
        WaveGenerator(float freql, float freqr, float amp, float offset)
            : left_freq(freql), right_freq(freqr), amplitude(amp), offset(offset)
        {}

        float left_freq; /**< Left channel frequency */
        float right_freq; /**< Right channel frequency */
        // Note: will be clamped to [-1, 1]
        float amplitude;  /**< Wave amplitude */
        float offset;  /**< Offset from 0 */
    };
}

#endif // _LIBLMTKAUDIO_WAVEGENERATOR_H_
