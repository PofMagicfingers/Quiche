#include "Beer.h"

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    score_label = "bieres";
    level_music = "!connemara";
    runningTimer = new Timer(_arduboy);
    beerSprite = new BeerSprite(_arduboy);
    beerSprite->x = 50;
    beerSprite->y = 20;
}

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed) : Beer(arduboy, speed, 0) {}

void Beer::newBeer()
{
    currentBeerState = BeerState::FULL;
    currentBeer++;
    currentBeerSips = 0;
    currentBeerMaxSips = (5 + rand() % 4);
    currentBeerSipsStep = (currentBeerMaxSips / 5.0);
}

void Beer::setup()
{
    Stage::setup();

    currentBeer = 0;
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

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(2.5);
    }

    if (runningTimer->isElapsed())
    {
        runningTimer->stop();
        setStatus(StageStatus::RUNNING);
    }

    runningTimer->tick();
}

void Beer::runningLoop()
{
    if (_arduboy->justReleased(A_BUTTON) || _arduboy->justReleased(B_BUTTON))
        currentBeerSips++;

    BeerState state = (BeerState)round(currentBeerSips / currentBeerSipsStep);

    if (state != currentBeerState)
    {
        currentBeerState = state;

        // glouglou sound
        beerSprite->state = state;

        if (state == BeerState::EMPTY)
        {
            beerDrunk++;
            newBeer();
            score++;
        }
    }

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(5);
    }

    if (runningTimer->isElapsed())
    {
        runningTimer->stop();
        setStatus(StageStatus::ENDING);
    }

    _arduboy->setCursor(0, 0);
    _arduboy->print("score: ");
    _arduboy->print(score);
    _arduboy->println(" " + score_label);

    runningTimer->tick();
    beerSprite->draw();
    
    _arduboy->display(CLEAR_BUFFER);
}

void Beer::endingLoop()
{
    _arduboy->setCursor(0, 0);
    _arduboy->println("ending!");
    _arduboy->print("uptime: ");
    _arduboy->print(runningTimer->timeElapsed());
    _arduboy->display(CLEAR_BUFFER);

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(2.5);
    }

    if (runningTimer->isElapsed())
    {
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
