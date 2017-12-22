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
        tunes->initChannel(PIN_SPEAKER_2);

        tunes->toneMutesScore(true);

        setupDone = true;
    }
}

BoomBox::~BoomBox()
{
    delete tunes;
}

void BoomBox::playRandom()
{
    randomSeed(analogRead(A0));
    int itrack = random(0, 1);
    play((Music)itrack);
}

void BoomBox::play(Music track)
{
    randomSeed(analogRead(A0));
    int itrack = round(random(1, 4));
        
    switch (track)
    {
    case Music::FEDER:
        tunes->playScore(itrack == 1 ? feder_t1 : itrack == 2 ? feder_t2 : feder_t3);
        break;
    case Music::CONNEMARA:
        tunes->playScore(itrack == 1 ? connemara_t1 : itrack == 2 ? connemara_t2 : connemara_t3);
        break;
    case Music::RANDOM:
        playRandom();
        break;
    }
}

void BoomBox::setSpeed(float speed)
{
    tunes->scorePlaybackSpeed(speed);
}

void BoomBox::stop()
{
    tunes->stopScore();
}

boolean BoomBox::isPlaying()
{
    return tunes->playing();
}