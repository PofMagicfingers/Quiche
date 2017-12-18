#ifndef QUICHE_TIMER_H
#define QUICHE_TIMER_H

#include <Arduboy2.h>

class Timer
{
  public:
    Timer(Arduboy2 *arduboy);
    void setTimeout(float seconds);
    void tick();
    float timeElapsed();
    bool isElapsed();
    bool isRunning();
    void reset();
    
  private:
    Arduboy2 *arduboyPtr;
    int frameElapsed = 0;
    int timeOutSec = 0;
    bool running = false;
};

#endif
