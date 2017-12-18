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

    runningTimer = Timer(_arduboy);
    runningTimer.setTimeout(3.5);

    currentBeer = 0;
    beerDrunk = 0;
    score_label = "bières";
    level_music = "none";
    newBeer();
}

void Beer::startingLoop()
{
    (*_arduboy).setCursor(0, 0);
    (*_arduboy).println("starting !");
    (*_arduboy).print("uptime: ");
    (*_arduboy).print(runningTimer.timeElapsed());
    (*_arduboy).display(CLEAR_BUFFER);

    if(runningTimer.isElapsed()) {
        runningTimer.reset();
        runningTimer.setTimeout(5);
        setStatus(StageStatus::RUNNING);
    }    

    runningTimer.tick();
}

void Beer::runningLoop()
{
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

    (*_arduboy).setCursor(0, 0);
    (*_arduboy).println("running!");
    (*_arduboy).print("uptime: ");
    (*_arduboy).print(runningTimer.timeElapsed());
    (*_arduboy).display(CLEAR_BUFFER);

    if(runningTimer.isElapsed()) {
        wrapUp();
    }
    
    runningTimer.tick();
}

void Beer::endingLoop()
{
    (*_arduboy).setCursor(0, 0);
    (*_arduboy).println("finished!");    
    (*_arduboy).display(CLEAR_BUFFER);
    finished = true;
}

void Beer::wrapUp()
{
    (*_arduboy).setCursor(0, 0);
    (*_arduboy).println("bye !");
    (*_arduboy).display(CLEAR_BUFFER);
    Stage::wrapUp();
    boomBox.stop();
}
