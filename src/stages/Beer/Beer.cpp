#include "Beer.h"

Beer::Beer(Arduboy2 *arbuboyPtr, StageSpeed speed) : 
    Stage(arbuboyPtr, speed) {
    if((int)speed > 3) {
        maxBeer = (int)speed - (rand() % 3);
    } else {
        maxBeer = (int)speed + (rand() % 3);
    }
}

void Beer::newBeer() {
    currentBeerState = BeerState::FULL;
    currentBeer++;
    currentBeerSips = 0;
    currentBeerMaxSips = (5 + rand() % 4);
    currentBeerSipsStep = (currentBeerMaxSips/5.0);
}

void Beer::setup()
{
    Stage::setup();
    currentBeer = 0;
    beerDrunk = 0;
    maxBeer = 0;
    score_label = "bières";
    level_music = "none";
    newBeer();
}

void Beer::loop() {
    Stage::loop();
}


void Beer::startingLoop()
{
    Stage::startingLoop();
    stageStatus = StageStatus::RUNNING;
    (*arduboy).printLn("coucou !")
}

void Beer::runningLoop()
{
    Stage::runningLoop();
    if(beerDrunk >= maxBeer) {
        wrapUp();
    } else {
        BeerState state = (BeerState)round(currentBeerSips/currentBeerSipsStep);

        if(state != currentBeerState) {
            currentBeerState = state;
            // glouglou sound
            // beerSprite.setStep((int)state);
            // beerSprite.draw()

            if(state == BeerState::EMPTY) {
                beerDrunk++;
                newBeer();
                score++;
            }
        }
    }
    if((*_arduboy).everyXFrames(50)) {
        (*arduboy).printLn("bye !")
        wrapUp();
    }
}

void Beer::endingLoop()
{
    Stage::endingLoop();
    finished = true;
}

void Beer::wrapUp()
{
    Stage::wrapUp();
    boomBox.stop();
}
