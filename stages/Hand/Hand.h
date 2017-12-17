#ifndef Hand_h
#define Hand_h

#include "stages/Stage.h"

class Hand : public Stage
{
    public:
        Hand(Arduboy2 *arbuboy);
        void setup();
        void loop();
        bool isFinished();
        int getScore();
        std::string getScoreLabel();

    private:
        Arduboy2 *_arduboy
        std::string score_label;        
}

#endif