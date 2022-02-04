#include "sinewave.h"

namespace audio {

    SineWave::SineWave(float freql, float freqr, float amp)
        : SineWave(freql, freqr, amp, 0)
    {
    }

    SineWave::SineWave(float freql, float freqr, float amp, float offset)
        : WaveGenerator(freql, freqr, amp, offset)
    {
    }

    void SineWave::operator()(AudioTrack& track)
    {
        unsigned long sample_rate = track.sampleRate();
        for (unsigned long i = 0; i < track.sampleLength(); i++)
        {
            audio_sample sample{};
            sample.left = amplitude * sin(2 * PI * left_freq / sample_rate * i) + offset;
            sample.right = amplitude * sin(2 * PI * right_freq / sample_rate * i) + offset;
            track.setSample(i, sample);
        }
    }

}