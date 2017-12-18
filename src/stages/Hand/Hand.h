#ifndef Hand_h
#define Hand_h

#include "../Stage.h"

class Hand : public Stage
{
    public:
        Hand(Arduboy2 *arbuboy);
        void setup();
        void loop();
        bool isFinished();
        int getScore();
        String getScoreLabel();

    private:
        Arduboy2 *_arduboy
        String score_label;        
}

#endif