#ifndef QUICHE_BOOMBOX_H
#define QUICHE_BOOMBOX_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

class BoomBox
{
  public:
    void setup(Arduboy2 *arduboy);
    void play(String track);
    void playRandom();
    void setSpeed(float speed);   
    void stop();
    boolean isPlaying();
    
  private:
    Arduboy2 *arduboyPtr;
    ArduboyPlaytune *tunes;
    bool setupDone = false;
};

#endif
