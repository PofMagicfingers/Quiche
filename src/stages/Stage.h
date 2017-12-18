#ifndef Stage_h
#define Stage_h

#include <Arduboy2.h>
#include "../BoomBox.h"

enum class StageSpeed {
    SLOW,
    NORMAL,
    SPEEDY,
    FAST,
    INSANE
};

enum class StageStatus {
    STARTING,
    RUNNING,
    ENDING
};

class Stage
{
    public:
        Stage(Arduboy2 *arbuboy, StageSpeed speed);
        virtual void setup();
        virtual void loop();
        virtual void wrapUp();
        bool isFinished();
        int getScore();
        String getScoreLabel();

    protected:
        virtual void startingLoop();
        virtual void runningLoop();
        virtual void endingLoop();

        Arduboy2 *_arduboy;
        String score_label;
        String level_music;
        int score;
        bool finished;
        StageStatus stageStatus;
        StageSpeed speed;
        BoomBox boomBox;        
};

#endif