#ifndef Hand_h
#define Hand_h

#include "../Stage.h"
#include <Arduboy2.h>

#include "./src/Direction.h"
#include "./src/QuicheSprite.h"
#include "./src/BallSprite.h"
#include "./src/GoalSprite.h"

const char BALLSTOPPED_STR[] = " arret";
const char BALLSSTOPPED_STR[] = " arrets";

class Hand : public Stage
{
    public:
        Hand(Arduboy2 *arbuboy, StageSpeed speed, BoomBox *bbox);
        void setup();
        ~Hand();

    private:
        void startingLoop();
        void runningLoop();
        void endingLoop();
        void wrapUp();
        
        void printInstructions();
        void drawTimer(double time);

        Direction ballDirection;

        GoalSprite *goalSprite;
        QuicheSprite *quicheSprite;
        BallSprite *ballSprite;
        
        Point ballStartPosition;
        Point ballEndPosition;
};

#endif