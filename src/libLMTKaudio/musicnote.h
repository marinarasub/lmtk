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
 * @file musicnote.h
 * @author marinarasub
 * @date January 2022
 * @brief Contains handy constants and conversions from musical notes (letters)
 * to frequencies.
 */

#ifndef _LIBLMTKAUDIO_MUSICNOTE_H_
#define _LIBLMTKAUDIO_MUSICNOTE_H_
#pragma once

#include <math.h>


namespace audio {

    namespace MusicalNote
    {
        // TODO use enum instead?

        typedef int Note; // in delta semitones from A4 below:
        constexpr double DEFAULT_A4_HZ = 440.0;

        /* ALL NOTES from 1-8 octave */ // TODO finish
        constexpr Note C_4 = -9, C_MIDDLE = -9;
        constexpr Note C_SHARP_4 = -8, D_FLAT_4 = -8;
        constexpr Note D_4 = -7;
        constexpr Note D_SHARP_4 = -6, E_FLAT_4 = -6;
        constexpr Note E_4 = -5;
        constexpr Note F_4 = -4;
        constexpr Note F_SHARP_4 = -3, G_FLAT_4 = -3;
        constexpr Note G_4 = -2;
        constexpr Note G_SHARP_4 = -1, A_FLAT_4 = -1;
        constexpr Note A_4 = 0;
        constexpr Note A_SHARP_4 = 1, B_FLAT_4 = 1;
        constexpr Note B_4 = 2;

        constexpr Note C_5 = 3;
        constexpr Note C_SHARP_5 = 4, D_FLAT_5 = 4;
        constexpr Note D_5 = 5;
        constexpr Note D_SHARP_5 = 6, E_FLAT_5 = 6;
        constexpr Note E_5 = 7;
        constexpr Note F_5 = 8;
        constexpr Note F_SHARP_5 = 9, G_FLAT_5 = 9;
        constexpr Note G_5 = 10;
        constexpr Note G_SHARP_5 = 11, A_FLAT_5 = 11;
        constexpr Note A_5 = 12;
        constexpr Note A_SHARP_5 = 13, B_FLAT_5 = 13;
        constexpr Note B_5 = 14;

        constexpr Note C_6 = 15;

        /**
        * @param note The musical note
        * @return The frequency of a note n semitones from A440
        */
        double getFrequency(Note note) {
            return DEFAULT_A4_HZ * pow(2, 1.0 / 12.0 * note);
        }

        /**
        * @param A4Freq The A4 frequency to tune to
        * @param note The musical note
        * @return The frequency of a note n semitones from custom A4 frequency
        */
        double getFrequency(double A4Freq, Note note) {
            return A4Freq * pow(2, 1.0 / 12.0 * note);
        }
    }
}

#endif // _LIBLMTKAUDIO_MUSICNOTE_H_