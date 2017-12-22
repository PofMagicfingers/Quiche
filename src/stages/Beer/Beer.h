#ifndef Beer_h
#define Beer_h

#include "../Stage.h"
#include <Arduboy2.h>

#include "./src/BeerState.h"
#include "./src/BeerSprite.h"

class Beer : public Stage
{
    public:
        Beer(Arduboy2 *arbuboy, StageSpeed speed, BoomBox *bbox);
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

        Point scorePosition;
};

#endif