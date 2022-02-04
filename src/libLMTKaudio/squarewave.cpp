#include "squarewave.h"

namespace audio {

    SquareWave::SquareWave(float freql, float freqr, float amp)
        : SquareWave(freql, freqr, amp, 0)
    {
    }

    SquareWave::SquareWave(float freql, float freqr, float amp, float offset)
        : WaveGenerator(freql, freqr, amp, offset)
    {
    }

    void SquareWave::operator()(AudioTrack& track)
    {
        unsigned long sample_rate = track.sampleRate();
        float l = amplitude, r = amplitude;
        float l_counter = 0, r_counter = 0;
        float left_period = sample_rate / left_freq;
        float right_period = sample_rate / right_freq;

        for (unsigned long i = 0; i < track.sampleLength(); i++)
        {
            audio_sample sample{};
            if (l_counter > left_period) { l = -l; l_counter = 0; }
            if (r_counter > right_period) { r = -r; r_counter = 0; }
            sample.left = l + offset;
            sample.right = r + offset;
            track.setSample(i, sample);
            l_counter++; r_counter++;
        }
    }


}