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
 * @file audiofilter.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains abstract audio filter class.
 */

#ifndef _LIBLMTKAUDIO_AUDIOFILTER_H_
#define _LIBLMTKAUDIO_AUDIOFILTER_H_
#pragma once

#include "audiotrack.h"


namespace audio {

    /**
    * @class AudioFilter "audiofilter.h"
    * @brief Abstract audio filter class.
    */
    class AudioFilter
    {
    public:

        /**
        * Virtual destructor.
        */
        virtual ~AudioFilter() {};

        /**
        * Abstract operator to an audio track
        * 
        * @param track Audio track to filter
        */
        virtual void operator()(AudioTrack& track) = 0;
    };
}

#endif // _LIBLMTKAUDIO_AUDIOFILTER_H_
