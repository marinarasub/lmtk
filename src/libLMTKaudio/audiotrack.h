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
 * @file audiotrack.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains class for a AudioTrack of audio samples which can be played
 */

#ifndef _LIBLMTKAUDIO_AUDIOTRACK_H_
#define _LIBLMTKAUDIO_AUDIOTRACK_H_
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <math.h>


namespace audio {

    typedef unsigned char byte;

    /**
    * @struct audio_sample "audiotrack.h"
    * @brief a 2 channel (stereo) audio sample of values [-1, 1]
    */
    struct audio_sample
    {
        float left; /**< Left channel sample. */
        float right; /**< Right channel sample. */

        /**
        * operator+: Adds two audio samples together.
        * 
        * Both channels are added linearly
        */
        audio_sample operator+(const audio_sample& other) const
        {
            audio_sample s{};
            s.left = this->left + other.left;
            s.right = this->right + other.right;
            s.clamp();
            return s;
        }

        /**
        * Clamp each channel to [-1, 1].
        */
        void clamp();
    };

    /** 
    * @class AudioTrack "audiotrack.h"
    * @brief Class for an AudioTrack containing audio samples which can be 
    * played, edited or written to a writeable format.
    * @see AudioPlayer
    */
    class AudioTrack
    {
        // const for number of channels
        static constexpr byte MONO = 1;
        // const for number of channels
        static constexpr byte STEREO = 2;

        /** The default sample rate. */
        static constexpr unsigned int DEFAULT_SAMPLE_RATE = 44100;
        // 44.1, 48 and multiples/factors of these.

    public:

        // TODO create with time in seconds?
        
        /**
        * Create an empty audio track of length 0.
        */
        AudioTrack();

        /**
        * Create and audio track with n samples at default sample rate.
        * 
        * @param length Length in samples
        */
        AudioTrack(unsigned long length);

        /**
        * Create and audio track with n samples and sample rate.
        *
        * @param length Length in samples
        * @param sample_rate Sample rate in hz
        */
        AudioTrack(unsigned long length, unsigned long sample_rate); // in samples

        /**
        * Copy constructor.
        * 
        * Clear current data and copy all sample and track data to *this
        * @param other Track to copy
        */
        AudioTrack(const AudioTrack& other);

        /**
        * Delete all sample data.
        */
        ~AudioTrack();

        /**
        * Assignment operator: sets this track equal to given one.
        * 
        * @param other Track to copy
        * @return Copied audio track
        */
        AudioTrack operator=(const AudioTrack& other);

        /**
        * operator+: Adds two audio tracks.
        *
        * Adds by adding each sample data together. Also known as track mixing.
        * @param other Track to add
        * @return Result of mixing two tracks
        */
        AudioTrack operator+(const AudioTrack& other) const;


        /**
        * @return The sample rate
        */
        unsigned int sampleRate() const;
        
        /**
        * @return The length of track in samples
        */
        unsigned long sampleLength() const;

        /**
        * @return The number of audio channels
        */
        byte channels() const;

        /**
        * Resets the cursor to START_POS.
        */
        void resetPosition();

        /**
        * @return Current cursor position in the track
        */
        unsigned long currentPos() const;

        /**
        * @return If the cursor has reached the end of the track
        */
        bool ended() const;

        /**
        * Using the track cursor, get the next sample and move the cursor by 1.
        * 
        * @returns The next audio sample at the cursor
        */
        audio_sample nextSample();

        /**
        * Get the sample at given position in track.
        * 
        * @param idx Index of sample
        */
        audio_sample getSample(unsigned long idx) const;

        /**
        * Set the sample at given index with an audio sample.
        * 
        * @param idx Index of sample to set
        * @param data Audio sample to set to
        */
        void setSample(unsigned long idx, audio_sample data);

        // TODO resample method
        /**
        * Resample the audio data to a new sample rate with minimal alteration 
        * to sound.
        * 
        * @param new_sample_rate New sample rate
        */
        void resample(unsigned long new_sample_rate);

        /**
        * Adds given track to *this one.
        * 
        * @see operator+
        * @param track Track to merge with
        */
        void merge(AudioTrack& track);

    protected:

        /**
        * Copies an audio track to *this, including audio data and track info.
        * 
        * @param other Track to copy
        */
        void copy(const AudioTrack& other);

        /**
        * Clear audio sample data.
        */
        void clear();

        //audio_sample clampSample(audio_sample& sample) const;


        audio_sample* audio; /**< Array of audio samples of the track */

    private:

        /**
        * Allocate array of audio samples in memory.
        * 
        * @param length Length of array to allocate, in samples
        */
        void allocSamples(size_t length);

        unsigned int sample_rate; /**< Intended sample rate for playback*/

        unsigned long current_pos; /**< Cursor for current position in track */

        unsigned long length; /**< Length of audio sample array */

        // TODO only support stereo currently
        byte num_tracks; /**< Number of audio channels in track */

    };
}

#endif // _LIBLMTKAUDIO_AUDIOTRACK_H_