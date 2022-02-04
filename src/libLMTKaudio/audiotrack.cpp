#include "audiotrack.h"

namespace audio {

    constexpr int START_POS = 0;

    // TODO variable sample rate
    AudioTrack::AudioTrack()
    {
        audio = nullptr;
        length = 0;
        num_tracks = 0;
        sample_rate = 0;
        current_pos = START_POS;
    }

    // defaults
    AudioTrack::AudioTrack(unsigned long length)
        : AudioTrack(length, DEFAULT_SAMPLE_RATE)
    {
    }

    AudioTrack::AudioTrack(unsigned long length, unsigned long sample_rate)
        : num_tracks(STEREO), sample_rate(sample_rate), current_pos(START_POS)
    {
        if (length == 0) throw std::invalid_argument("Length cannot be 0");
        allocSamples(length);
    }

    AudioTrack::AudioTrack(const AudioTrack& other) : AudioTrack()
    {
        copy(other);
    }

    AudioTrack::~AudioTrack()
    {
        clear();
    }

    AudioTrack AudioTrack::operator=(const AudioTrack& other)
    {
        if (this != &other) copy(other); // TODO != for object not ptr
        return *this;
    }

    AudioTrack AudioTrack::operator+(const AudioTrack& other) const
    {
        // TODO resample etc.
        unsigned long max_len = this->sampleLength() > other.sampleLength() ?
            this->sampleLength() : other.sampleLength();
        AudioTrack mix(max_len); // TODO pass in sample rate etc.
        for (unsigned long i = 0; i < max_len; i++)
        {
            audio_sample add = this->getSample(i) + other.getSample(i);
            mix.setSample(i, add);
        }
        return mix;
    }



    unsigned int AudioTrack::sampleRate() const
    {
        return sample_rate;
    }

    unsigned long AudioTrack::sampleLength() const
    {
        return length;
    }

    byte AudioTrack::channels() const
    {
        return num_tracks;
    }

    void AudioTrack::resetPosition()
    {
        current_pos = START_POS;
    }

    unsigned long AudioTrack::currentPos() const
    {
        return current_pos;
    }

    bool AudioTrack::ended() const
    {
        return current_pos >= length;
    }

    // return ???if end
    audio_sample AudioTrack::nextSample()
    {
        //if (currentPos() < 0) throw 0xFFFFFFFF; // placeholder
        audio_sample next{ 0, 0 };
        if (!ended()) {
            next = audio[currentPos()];
            current_pos++;
        }
        return next;
    }

    audio_sample AudioTrack::getSample(unsigned long idx) const
    {
        if (idx >= sampleLength()) return audio_sample{ 0, 0 };
        return audio[idx];
    }

    void AudioTrack::setSample(unsigned long idx, audio_sample data)
    {
        //if (idx > sampleLength()) TODO realloc if idx out of range
        data.clamp();
        audio[idx] = data;
    }

    // TODO linear interp.
    // uses nearest neighbor
    void AudioTrack::resample(unsigned long new_sample_rate)
    {
        // TODO
        if (new_sample_rate == 0) throw std::invalid_argument("sample rate cannot be < 1");
        if (!audio) throw std::runtime_error("no audio data to resample");

        double ratio = (double)sample_rate / new_sample_rate;
        unsigned long new_len = (unsigned long)(1.0 / ratio * sampleLength());
        if (new_len == 0) throw std::runtime_error("error: resampled track length is 0");

        AudioTrack temp(new_len, new_sample_rate);
        for (unsigned long i = 0; i < new_len; i++)
        {
            // nearest neighbor resample
            temp.setSample(i, getSample((unsigned long)floor(ratio * i)));
        }
        *this = temp;
    }

    void AudioTrack::merge(AudioTrack& other)
    {
        *this = *this + other;
    }



    void AudioTrack::copy(const AudioTrack& other)
    {
        clear();
        allocSamples(other.length);
        this->num_tracks = other.num_tracks;
        this->sample_rate = other.sampleRate();
        for (unsigned long i = 0; i < length; i++)
        {
            this->setSample(i, other.getSample(i));
        }
    }

    void AudioTrack::clear()
    {
        if (audio != nullptr)
        {
            delete[] audio;
            audio = nullptr;
        }
    }

    void AudioTrack::allocSamples(size_t length)
    {
        this->length = length;
        audio = new audio_sample[length];
    }

    void audio::audio_sample::clamp()
    {
        left = fmin(1.0, fmax(-1.0, left));
        right = fmin(1.0, fmax(-1.0, right));
    }
}
