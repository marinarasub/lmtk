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
 * @file sinewave.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing sine wave generator
 */

#ifndef _LIBLMTKAUDIO_SINEWAVE_H_
#define _LIBLMTKAUDIO_SINEWAVE_H_
#pragma once

#include <math.h>
#include "wavegenerator.h"


namespace audio {

    /**
    * @class SineWave "sinewave.h"
    * @brief Class for generating a sine wave
    * @see WaveGenerator
    */
    class SineWave : public WaveGenerator
    {
    public:
        
        /**
        * Create a sine wave given frequency and amplitude.
        *
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        */
        SineWave(float freql, float freqr, float amp);

        /**
        * Create a sine wave given frequency, amplitude and offset.
        *
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        * @param offset Offset from 0
        */
        SineWave(float freql, float freqr, float amp, float offset);

        /**
        * Sine wave operator.
        *
        * Creates a sine wave over the track, overwriting existing data
        */
        void operator()(AudioTrack& track);

    };
}

#endif // _LIBLMTKAUDIO_SINEWAVE_H_