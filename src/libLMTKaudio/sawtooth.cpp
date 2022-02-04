#include "sawtooth.h"

namespace audio {

    SawtoothWave::SawtoothWave(float freql, float freqr, float amp)
        : SawtoothWave(freql, freqr, amp, 0)
    {
    }

    SawtoothWave::SawtoothWave(float freql, float freqr, float amp, float offset)
        : WaveGenerator(freql, freqr, amp, offset)
    {
    }

    void SawtoothWave::operator()(AudioTrack& track)
    {
        unsigned long sample_rate = track.sampleRate();
        float l = -amplitude, r = -amplitude;
        float left_period = sample_rate / left_freq;
        float right_period = sample_rate / right_freq;

        for (unsigned long i = 0; i < track.sampleLength(); i++)
        {
            audio_sample sample{};
            if (l > amplitude) l = -amplitude;
            if (r > amplitude) r = -amplitude;
            sample.left = l + offset;
            sample.right = r + offset;
            track.setSample(i, sample);
            l += amplitude / left_period;
            r += amplitude / right_period;
        }
    }
}
