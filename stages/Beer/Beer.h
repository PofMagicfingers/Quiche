#ifndef Beer_h
#define Beer_h

#include "Arduboy2/src/Arduboy2.h"
#include <string>

enum class BeerState {
    FULL = 1,
    TOP,
    HALF,
    BOTTOM,
    EMPTY
}

class Beer : public Stage
{
    public:
        Stage(Arduboy2 *arbuboy);
        void setup();
        void loop();
        bool isFinished();
        int getScore();
        std::string getScoreLabel();

    private:
        int currentBeer;
        int currentBeerSips;
        int currentBeerMaxSips;
        float currentBeerSipsStep;
        int beerDrunk;
        int maxBeer;
        BeerState currentBeerState;
}

#endif