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
 * @file flac.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains class for read/writing and using a FLAC file as an audio track
 */


#ifndef _LIBLMTKAUDIO_FLAC_H_
#define _LIBLMTKAUDIO_FLAC_H_
#pragma once

#include <stdlib.h>
#include <string>
#include <FLAC++/all.h>
#include "audiotrack.h"
#include "../utils/utils.h"


namespace FLACAPI = FLAC; // to avoid confusion between libFLAC API

namespace audio {

    /**
    * @class FLAC "flac.h"
    * @brief Class for a FLAC file audio track
    * @see AudioTrack
    */
    class FLAC : public AudioTrack
    {

        /**
        * @class FLACDecoder "flac.h"
        * @brief Class for FLAC decoding using libFLAC++ API
        */
        class FLACDecoder : public FLACAPI::Decoder::File
        {
        public:
            FLACDecoder() : FLACAPI::Decoder::File()
            {
                out = NULL;
            }

            ~FLACDecoder()
            {
                if (out != NULL) delete out;
            }

            // return constructed flac. call after read done.
            FLAC get();

        private:

            virtual FLAC__StreamDecoderWriteStatus write_callback(
                const FLAC__Frame* frame,
                const FLAC__int32* const* buffer) override;

            virtual void metadata_callback(
                const FLAC__StreamMetadata* metadata) override;

            virtual void error_callback(
                FLAC__StreamDecoderErrorStatus status) override;

            FLAC* out;

            bool finished = false;

            unsigned int bit_depth = 0; // of samples
        };

    public:

        /**
        * Creates a FLAC of length in samples, at default sample rate.
        * 
        * @param length Length in audio samples
        */
        FLAC(unsigned long length); 

        /**
        * Creates a FLAC of length in samples, at given sample rate.
        * 
        * @param length Length in audio samples
        * @param sample_rate Sample rate in hz
        */
        FLAC(unsigned long length, unsigned long sample_rate); 

        /**
        * Creates FLAC from file on disk.
        * 
        * @see readFile()
        * @param path Path to file
        */
        FLAC(std::string path);

        /**
        * Reads a FLAC file from disk into memory.
        * 
        * @param path Path to file
        */
        bool readFile(std::string path);

        // TODO !!! NOT IMPLEMENTED
        bool writeFile(std::string path);

    };
}

#endif //_LIBLMTKAUDIO_FLAC_H_
