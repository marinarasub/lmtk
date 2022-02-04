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
 * @file sawtooth.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing sawtooth wave generator
 */

#ifndef _LIBLMTKAUDIO_SAWTOOTH_H_
#define _LIBLMTKAUDIO_SAWTOOTH_H_
#pragma once

#include <math.h>
#include "wavegenerator.h"


namespace audio {

    /**
    * @class SawtoothWave "sawtoothwave.h"
    * @brief Class for generating a sawtooth wave
    * 
    * A sawtooth wave is a triangular wave with a linear rise, and sharp fall.
    * @see WaveGenerator
    */
    class SawtoothWave : public WaveGenerator
    {
    public:
        
        /**
        * Create a sawtooth wave given frequency and amplitude.
        *
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        */
        SawtoothWave(float freql, float freqr, float amp);

        /**
        * Create a sawtooth wave given frequency, amplitude and offset.
        *
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        * @param offset Offset from 0
        */
        SawtoothWave(float freql, float freqr, float amp, float offset);

        /**
        * Sawtooth operator.
        *
        * Creates a sawtooth wave over the track, overwriting existing data
        */
        void operator()(AudioTrack& track);

    };
}

#endif // _LIBLMTKAUDIO_SAWTOOTH_H_

