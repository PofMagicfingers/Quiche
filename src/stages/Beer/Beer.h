#ifndef Beer_h
#define Beer_h

#include "../Stage.h"
#include <Arduboy2.h>

#include "./src/BeerState.h"
#include "./src/BeerSprite.h"

const char BEERDRUNK_STR[] = " biere";
const char BEERSDRUNK_STR[] = " bieres";

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

        void drawTimer(double time);
        void showInstructions();
        
        int currentBeerSips;
        BeerState currentBeerState;

        BeerSprite * beerSprite;

        Point scorePosition;
};

#endif