#ifndef QUICHE_TIMER_H
#define QUICHE_TIMER_H

#include <Arduboy2.h>

class Timer
{
  public:
    Timer(Arduboy2 *arduboy);
    void setTimeout(int seconds);
    void setTimeout(double seconds);
    void tick();
    float timeElapsed();
    bool isElapsed();
    bool isRunning();
    void reset();
    void stop();
    int frameElapsed;
    double timeOutSec;
    bool running;
    bool stopped;

  private:
    Arduboy2 *arduboyPtr;
  };

#endif
