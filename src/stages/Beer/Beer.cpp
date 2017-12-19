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
    currentBeer = 0;
    beerDrunk = 0;
    score_label = "bières";
    level_music = "!connemara";
    newBeer();

    // sceneTimer = Timer(_arduboy);
    // sceneTimer.setTimeout(2.5);
    Stage::setup();    
}

void Beer::startingLoop()
{
    (*_arduboy).setCursor(0, 0);
    (*_arduboy).println("starting !");
    // (*_arduboy).print("uptime: ");
    // (*_arduboy).println(sceneTimer.timeElapsed());
    // (*_arduboy).print("f elap: ");
    // (*_arduboy).println(sceneTimer.frameElapsed);
    (*_arduboy).display(CLEAR_BUFFER);

    // if(sceneTimer.isElapsed()) {
    //     sceneTimer.stop();
    //     setStatus(StageStatus::RUNNING);
    // }

    // sceneTimer.tick();    
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
    // (*_arduboy).print("uptime: ");
    // (*_arduboy).print(sceneTimer.timeElapsed());
    (*_arduboy).display(CLEAR_BUFFER);


    // if(!sceneTimer.isRunning()) {
    //     sceneTimer.reset();
    //     sceneTimer.setTimeout(5);
    // }

    // if(sceneTimer.isElapsed()) {
    //     sceneTimer.stop();
    //     setStatus(StageStatus::ENDING);
    // }

    // sceneTimer.tick();
}

void Beer::endingLoop()
{
    // (*_arduboy).setCursor(0, 0);
    // (*_arduboy).println("wrapping up in 2.5 !");    
    // (*_arduboy).display(CLEAR_BUFFER);

    // if(!sceneTimer.isRunning()) {
    //     sceneTimer.reset();
    //     sceneTimer.setTimeout(2.5);
    // }

    // if(sceneTimer.isElapsed()) {
    //     sceneTimer.stop();
    //     wrapUp();
    // }
    
    // sceneTimer.tick();
}