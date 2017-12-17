#include "Beer.h"

using namespace std;

Beer::Beer(Arduboy2 *arbuboy, StageSpeed speed) : Stage::Stage(arduboy, speed) {
    if(speed > 3) {
        maxBeer = speed - (rand() % 3)
    } else {
        maxBeer = speed + (rand() % 3)
    }
}

void Beer::newBeer() {
    currentBeerState = BeerState::FULL;
    currentBeer++;
    currentBeerSips = 0
    currentBeerMaxSips = (5 + rand() % 4);
    currentBeerSipsStep = (currentBeerMaxSips/5.0);
}

void Beer::setup()
{
    Stage::setup();
    currentBeer = 0;
    beerDrunk = 0;
    maxBeer = 0;
    newBeer();
}

void Beer::startingLoop()
{
    Stage::startingLoop();
}

void Beer::runningLoop()
{
    Stage::runningLoop();
    if(beerDrunk >= maxBeer) {
        finished = true;
    } else {
        BeerState state = std::round(currentBeerSips/currentBeerSipsStep);

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
}

void Beer::endingLoop()
{
    Stage::endingLoop();
}

void Beer::wrapUp()
{
    Stage::wrapUp();
}

bool Beer::isFinished()
{
    return Stage::isFinished();

}

int Beer::getScore()
{
    return Stage::getScore();
}

string Beer::getScoreLabel()
{
    return "bières"
}