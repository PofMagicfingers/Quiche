#include "BoomBox.h"
#include "../assets/scores/connemara.h"
#include "../assets/scores/feder.h"

void BoomBox::setup(Arduboy2 *arduboy)
{
    if (!setupDone)
    {
        arduboyPtr = arduboy;
        tunes = ArduboyPlaytune((*arduboyPtr).audio.enabled);
        // audio setup
        tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
        // if not a DevKit
        tunes.initChannel(PIN_SPEAKER_2);
#else
        // if it's a DevKit
        tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
        tunes.toneMutesScore(true);       // mute the score when a tone is sounding
#endif
        tunes.toneMutesScore(true);

        setupDone = true;
    }
}

void BoomBox::play(String track) {
    if(track == "connemara") {
        tunes.playScore(connemara);
    }
    if(track == "feder") {
        tunes.playScore(feder);
    }
}

void BoomBox::setSpeed(float speed) {
    tunes.scorePlaybackSpeed(speed);
}

void BoomBox::stop() {
    tunes.stopScore();
}

boolean BoomBox::isPlaying() {
    return tunes.playing();
}