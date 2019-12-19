#ifndef QUICHE_BOOMBOX_H
#define QUICHE_BOOMBOX_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyPlaytune.h>

enum class Music {
  FEDER = 0, 
  CONNEMARA,
  RANDOM
};

class BoomBox
{
  public:
    void setup(Arduboy2 *arduboy);
    void play(Music track);
    void playRandom();
    void setSpeed(float speed);   
    void stop();
    boolean isPlaying();
    ArduboyPlaytune *tunes;
    ~BoomBox();

  private:
    Arduboy2 *arduboyPtr;
    bool setupDone = false;
};

#endif
