#include "Timer.h"

Timer::Timer(Arduboy2 *arduboy) : arduboyPtr(arduboy)
{
}

void Timer::setTimeout(float seconds) {
    timeOutSec = seconds;
}

void Timer::tick() {
    frameElapsed++;
    running = true;
}

float Timer::timeElapsed() {
    return ((float)frameElapsed / (*arduboyPtr).getFrameRate());
}

bool Timer::isElapsed() {
    return timeElapsed() >= timeOutSec;
}

bool Timer::isRunning() {
    return running;
}

void Timer::reset() {
    frameElapsed = 0;
    running = false;
}