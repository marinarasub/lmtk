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
 * @file squarewave.h
 * @author marinarasub
 * @date January 2022
 * @brief File containing square wave generator
 */

#ifndef _LIBLMTKAUDIO_SQUAREWAVE_H_
#define _LIBLMTKAUDIO_SQUAREWAVE_H_
#pragma once

#include <math.h>
#include "wavegenerator.h"


namespace audio {

    /**
    * @class SquareWave "squarewave.h"
    * @brief Class for generating a square wave
    * @see WaveGenerator
    */
    class SquareWave : public WaveGenerator
    {
    public:
        
        /**
        * Create a square wave given frequency and amplitude.
        * 
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        */
        SquareWave(float freql, float freqr, float amp);

        /**
        * Create a square wave given frequency, amplitude and offset.
        * 
        * @param freql Left channel frequency
        * @param freqr Right channel frequency
        * @param amp Amplitude
        * @param offset Offset from 0
        */
        SquareWave(float freql, float freqr, float amp, float offset);

        /**
        * Square wave operator.
        * 
        * Creates a square wave over the track, overwriting existing data
        */
        void operator()(AudioTrack& track);


    };
}

#endif // _LIBLMTKAUDIO_SQUAREWAVE_H_

