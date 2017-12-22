#include "Timer.h"

Timer::Timer(Arduboy2 *arduboy) : arduboyPtr(arduboy)
{
    frameElapsed = 0;
    timeOutSec = 0;
    running = false;
    stopped = false;
}

Timer::~Timer() {
    delete arduboyPtr;
}

void Timer::setTimeout(double seconds) {
    timeOutSec = seconds;
}

void Timer::setTimeout(int seconds) {
    timeOutSec = (double)seconds;
}

void Timer::tick() {
    if(timeOutSec > 0 && !stopped) {
        frameElapsed++;
        running = true;
    }
}

float Timer::timeElapsed() {
    return ((float)frameElapsed / (*arduboyPtr).getFrameRate());
}

bool Timer::isElapsed() {
    return timeElapsed() >= timeOutSec;
}

bool Timer::isRunning() {
    return running && !stopped;
}

void Timer::stop() {
    stopped = true;
}

void Timer::reset() {
    frameElapsed = 0;
    timeOutSec = 0;
    running = false;
    stopped = false;
}