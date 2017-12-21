#include "BoomBox.h"
#include "../assets/scores/connemara.h"
#include "../assets/scores/feder.h"

void BoomBox::setup(Arduboy2 *arduboy)
{
    if (!setupDone)
    {
        arduboyPtr = arduboy;
        tunes = new ArduboyPlaytune(arduboyPtr->audio.enabled);
        // audio setup
        tunes->initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
        // if not a DevKit
        tunes->initChannel(PIN_SPEAKER_2);
#else
        // if it's a DevKit
        tunes->initChannel(PIN_SPEAKER_1); // use the same pin for both channels
        tunes->toneMutesScore(true);       // mute the score when a tone is sounding
#endif
        tunes->toneMutesScore(true);

        setupDone = true;
    }
}

BoomBox::~BoomBox() {
    delete tunes;
}

void BoomBox::playRandom() {
    String tracks[] = {"connemara", "feder"};

    randomSeed(analogRead(A0));
    int itrack = random(0, 1);
    play(tracks[itrack]);
}

void BoomBox::play(String track) {
    if(track == "connemara") {
        randomSeed(analogRead(A0));
        int itrack = round(random(1, 4));
        tunes->playScore(itrack == 1 ? connemara_t1 : itrack == 2 ? connemara_t2 :  connemara_t3);
    }
    if(track == "feder") {
        randomSeed(analogRead(A0));
        int itrack = round(random(1, 4));
        tunes->playScore(itrack == 1 ? feder_t1 : itrack == 2 ? feder_t2 :  feder_t3);
    }
    if(track == "random") {
        playRandom();        
    }
}

void BoomBox::setSpeed(float speed) {
    tunes->scorePlaybackSpeed(speed);
}

void BoomBox::stop() {
    tunes->stopScore();
}

boolean BoomBox::isPlaying() {
    return tunes->playing();
}