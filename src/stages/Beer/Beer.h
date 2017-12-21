#ifndef Beer_h
#define Beer_h

#include "../Stage.h"
#include <Arduboy2.h>
#include "../../Timer.h"

#include "./src/BeerState.h"
#include "./src/BeerSprite.h"

class Beer : public Stage
{
    public:
        Beer(Arduboy2 *arbuboy, StageSpeed speed, BoomBox *bbox);
        Beer(Arduboy2 *arbuboy, StageSpeed speed);
        void setup();
        ~Beer();

    private:
        void newBeer();
        void startingLoop();
        void runningLoop();
        void endingLoop();
        void wrapUp();

        int currentBeerSips;
        BeerState currentBeerState;

        BeerSprite * beerSprite;

        double speedFactor;
        double startDuration;
        double runningDuration;
        double endDuration;

        bool showGo = true;
        int percentage;

        Point scorePosition;

        Timer *runningTimer;
};

#endif