#ifndef Stage_h
#define Stage_h

#include "Arduboy2/src/Arduboy2.h"
#include <string>

enum class StageSpeed {
    SLOW,
    NORMAL,
    SPEEDY,
    FAST,
    INSANE
}

enum class StageStatus {
    STARTING,
    RUNNING,
    ENDING
}

class Stage
{
    public:
        Stage(Arduboy2 *arbuboy, StageSpeed speed);
        void setup();
        void loop();
        void wrapUp();
        bool isFinished();
        int getScore();
        std::string getScoreLabel();

    protected:
        void startingLoop();
        void runningLoop();
        void endingLoop();

        Arduboy2 *_arduboy
        std::string score_label;
        int score;
        bool finished;
        StageSpeed speed = StageSpeed::SLOW;
}

#endif