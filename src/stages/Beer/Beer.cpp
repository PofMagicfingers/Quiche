#include "Beer.h"

Beer::Beer(Arduboy2 *arbuboyPtr, StageSpeed speed) : 
    Stage(arbuboyPtr, speed) {
    if((int)speed > 3) {
        maxBeer = (int)speed - (rand() % 3);
    } else {
        maxBeer = (int)speed + (rand() % 3);
    }

    score_label = "bières";
    level_music = "connemara";
    runningTimer = new Timer(_arduboy);
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
    newBeer();

    setStatus(StageStatus::STARTING);
}

void Beer::startingLoop()
{
    _arduboy->setCursor(0, 0);
    _arduboy->println("starting !");
    _arduboy->println("music !");
    _arduboy->println(level_music);
    _arduboy->print("uptime: ");
    _arduboy->print(runningTimer->timeElapsed());
    _arduboy->display(CLEAR_BUFFER);

    if(!runningTimer->isRunning()) {
        runningTimer->reset();
        runningTimer->setTimeout(2.5);
    }

    if(runningTimer->isElapsed()) {
        runningTimer->stop();
        setStatus(StageStatus::RUNNING);
    }

    runningTimer->tick();
}

void Beer::runningLoop()
{
    // if(beerDrunk >= maxBeer) {
    //     wrapUp();
    // } else {
    //     BeerState state = (BeerState)round(currentBeerSips/currentBeerSipsStep);

    //     if(state != currentBeerState) {
    //         currentBeerState = state;
            // glouglou sound
            // beerSprite.setStep((int)state);
            // beerSprite.draw()

    //         if(state == BeerState::EMPTY) {
    //             beerDrunk++;
    //             newBeer();
    //             score++;
    //         }
    //     }
    // }

    _arduboy->setCursor(0, 0);
    _arduboy->println("running!");
    _arduboy->print("uptime: ");
    _arduboy->print(runningTimer->timeElapsed());
    _arduboy->display(CLEAR_BUFFER);

    if(!runningTimer->isRunning()) {
        runningTimer->reset();
        runningTimer->setTimeout(5);
    }

    if(runningTimer->isElapsed()) {
        runningTimer->stop();
        setStatus(StageStatus::ENDING);
    }
    
    runningTimer->tick();
}

void Beer::endingLoop()
{
    _arduboy->setCursor(0, 0);
    _arduboy->println("ending!");
    _arduboy->print("uptime: ");
    _arduboy->print(runningTimer->timeElapsed());
    _arduboy->display(CLEAR_BUFFER);

    if(!runningTimer->isRunning()) {
        runningTimer->reset();
        runningTimer->setTimeout(2.5);
    }

    if(runningTimer->isElapsed()) {
        wrapUp();
    }

    runningTimer->tick();
}

void Beer::wrapUp()
{
    _arduboy->setCursor(0, 0);
    _arduboy->println("bye !");
    _arduboy->display(CLEAR_BUFFER);
    Stage::wrapUp();
}
