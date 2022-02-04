#include "audioplayer.h"
#include <stdio.h>

namespace audio {

    AudioPlayer::AudioPlayer() : amplifier(1.0)
    {
        stream = nullptr;
        PaError err;
        err = Pa_Initialize();
        handle_pa_error(err);
    }

    AudioPlayer::~AudioPlayer()
    {
        close();
        handle_pa_error(Pa_Terminate());
    }

    void AudioPlayer::operator()(AudioTrack& track)
    {
        close();
        play(track);
    }

    void AudioPlayer::play(AudioTrack& track)
    {
        audio_track = &track;
        PaError err;
        /* Open an audio I/O stream. */
        err = Pa_OpenDefaultStream(&stream,
            0,          /* no input channels */
            2,          /* stereo output */
            paFloat32,  /* 32 bit floating point output */
            track.sampleRate(),
            paFramesPerBufferUnspecified, /* frames per buffer, i.e. the number
                               of sample frames that PortAudio will
                               request from the callback. Many apps
                               may want to use
                               paFramesPerBufferUnspecified, which
                               tells PortAudio to pick the best,
                               possibly changing, buffer size.*/
            playCallback, /* this is your callback function */
            this); /*This is a pointer that will be passed to
                               your callback*/
        handle_pa_error(err);

        track.resetPosition();
        err = Pa_StartStream(stream);
        handle_pa_error(err);

        //Pa_Sleep(1000); // handle duration?
        while (Pa_IsStreamActive(stream)) {}
    }

    void AudioPlayer::stop()
    { /// AbortStream() for immediate stop (forceq)
        if (stream == nullptr) return; // nothing to stop
        handle_pa_error(Pa_StopStream(stream));
    }


    void AudioPlayer::close()
    {
        if (stream == nullptr) return; // nothing to close
        stop();
        PaError err;
        err = Pa_CloseStream(stream);
        handle_pa_error(err);

    }

    AudioTrack* AudioPlayer::track()
    {
        return audio_track;
    }

    void AudioPlayer::setGain(float db)
    {
        amplifier = pow(10.0, db / 10.0); // db to ratio
    }

    int AudioPlayer::playCallback(
        const void* inputBuffer, // track audio array
        void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData)
    {
        /* Cast data passed through stream to our structure. */
        AudioPlayer* player = (AudioPlayer*)userData;
        if (!player) throw 0xFF; // if actually happends then WTF??
        AudioTrack* track = player->track();
        if (!track) return paAbort; // cant play nothing.
        audio_sample data = track->nextSample();

        float* out = (float*)outputBuffer;
        (void)inputBuffer; /* Prevent unused variable warning. */

        for (unsigned int i = 0; i < framesPerBuffer; i++)
        {
            if (track->ended()) return paComplete;
            *out++ = player->amplifier * (float)data.left;  /* left */
            *out++ = player->amplifier * (float)data.right;  /* right */
            data = track->nextSample();
        }

        return paContinue;
    }

    bool AudioPlayer::handle_pa_error(PaError err)
    {
        if (err != paNoError) {
            Pa_Terminate();
            throw err;
        }
        return true;
    }

}