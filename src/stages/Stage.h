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
        void setup();
        void loop();
        void wrapUp();
        bool isFinished();
        int getScore();
        String getScoreLabel();

    protected:
        virtual void startingLoop() = 0;
        virtual void runningLoop() = 0;
        virtual void endingLoop() = 0;
        void setStatus(StageStatus);

        Arduboy2 *_arduboy;
        String score_label;
        String level_music;
        int score;
        bool finished;
        StageSpeed speed;
        BoomBox boomBox;        
        int _secElapsed;

    private:
        StageStatus stageStatus;        
};

#endif