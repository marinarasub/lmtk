#include "audiotest.h"

using namespace ::testing;
using namespace audio;

// !!! TODO we need more tests! //

TEST(AudioTrackTest, constructor_basic) {
    try {
        AudioTrack test;
    }
    catch (...) {
        FAIL();
    }
}

TEST(AudioTrackTest, play_saw) {
    try {

        AudioTrack test(48000);
        SawtoothWave saw(440, 880, 0.33);
        AudioPlayer player;
        saw(test);
        player(test);
        
    }
    catch (...) {
        FAIL();
    }
}