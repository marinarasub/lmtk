#include <stdio.h>
#include "audioplayer.h"
#include "sinewave.h"
#include "sawtooth.h"
#include "squarewave.h"
#include "musicnote.h"
#include "flac.h"

//typedef int PaStreamCallback(
//    const void* input,
//    void* output,
//    unsigned long frameCount,
//    const PaStreamCallbackTimeInfo* timeInfo,
//    PaStreamCallbackFlags statusFlags,
//    void* userData
//);

using namespace MusicalNote;

// OLD TEST MAIN, use gtest now
int main()
{
    AudioPlayer player;
    AudioTrack ONE(44100 * 3);
    AudioTrack TWO(44100 * 3);
    AudioTrack THREE(44100 * 3);
    AudioTrack FOUR(44100 * 2);
    SawToothWave gen1(getFrequency(G_4), getFrequency(G_5), 0.15);
    SawToothWave gen2(getFrequency(B_4), getFrequency(B_5), 0.15);
    SawToothWave gen3(getFrequency(D_4), getFrequency(D_5), 0.15);
    SawToothWave gen4(getFrequency(G_5), getFrequency(G_5), 0.15);
    gen1.operator()(ONE);
    gen2.operator()(TWO);
    gen3.operator()(THREE);
    gen4.operator()(FOUR);
    
    AudioTrack chord = ONE + TWO + THREE + FOUR;
    player.play(chord);

    audio::FLAC read("../../audio/test2.flac");
    read.resample(96000);
    player.setGain(2.0);
    player.play(read);

   /* SineWave sine(440, 900, 0.6);
    sine.operator()(track);
    player.play(track);

    SawToothWave saw(440, 900, 0.3);
    saw.operator()(track);
    player.play(track);

    SquareWave sqr(440, 900, 0.3);
    sqr.operator()(track);
    player.play(track);*/

    return 0;

}