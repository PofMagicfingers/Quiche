#include "BoomBox.h"
#include "../lib/Arduboy2/src/Arduboy2.h"
#include "../lib/ArduboyPlaytune/src/ArduboyPlaytune.h"

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);
bool setupDone = false;

void BoomBox::setup()
{
    if (!setupDone)
    {
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