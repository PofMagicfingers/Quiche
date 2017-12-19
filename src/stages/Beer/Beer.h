#ifndef Beer_h
#define Beer_h

#include "../Stage.h"
#include <Arduboy2.h>
#include "../../Timer.h"

enum class BeerState {
    FULL = 1,
    TOP,
    HALF,
    BOTTOM,
    EMPTY
};

class Beer : public Stage
{
    public:
        Beer(Arduboy2 *arbuboy, StageSpeed speed);
        void setup();

    private:
        void newBeer();
        void startingLoop();
        void runningLoop();
        void endingLoop();
        
        int currentBeer;
        int currentBeerSips;
        int currentBeerMaxSips;
        float currentBeerSipsStep;
        int beerDrunk;
        int maxBeer;
        BeerState currentBeerState;

        Timer sceneTimer = 0;
};

#endif