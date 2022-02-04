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
 * @file audioplayer.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains class for playing an audio track
 */

#ifndef _LIBLMTKAUDIO_AUDIOPLAYER_H_
#define _LIBLMTKAUDIO_AUDIOPLAYER_H_
#pragma once

#include <portaudio.h>
#include "audiotrack.h"


namespace audio {

    /**
    * @class AudioPlayer "audioplayer.h"
    * @brief An audio player for audio tracks to device output
    * Uses portaudio for audio device IO
    */
    class AudioPlayer
    {
    public:

        /**
        * Create an audio player.
        * 
        * Opens an audio stream for playing
        */
        AudioPlayer();

        /**
        * Closes audio stream and terminates audio player.
        */
        ~AudioPlayer();

        /**
        * Audio track operator: play the selected track.
        * 
        * @see play()
        * @param track Audio track to play
        */
        virtual void operator()(AudioTrack& track);

        /**
        * Play the selected track to default audio device.
        * 
        * @param track Audio track to play
        */
        void play(AudioTrack& track);

        //void record(AudioTrack& track);

        /**
        * Stops playing the audio track.
        */
        void stop();

        /**
        * Close the audio stream, if open.
        */
        void close();

        /**
        * @return The audio track associated with the audio player
        */
        AudioTrack* track();

        /**
        * Sets the gain of the output sound.
        * 
        * @param db Gain in decibels
        */
        void setGain(float db); // in db (10log_10(out/in))

    private:

        /**
        * Callback function for audio playback with portaudio.
        */
        static int playCallback(
            const void* inputBuffer,
            void* outputBuffer,
            unsigned long framesPerBuffer,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void* userData);

        /**
        * Handle any PortAudio error given
        * 
        * @param err PortAudio error
        */
        bool handle_pa_error(PaError err);

        PaStream* stream; /**< Port Audio stream */

        AudioTrack* audio_track; /**< Audio track to play */

        float amplifier; /**< Linear gain scalar */

    };

}

#endif // _LIBLMTKAUDIO_AUDIOPLAYER_H_