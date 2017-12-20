#include "Beer.h"

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    score_label_singular = "biere";
    score_label = "bieres";
    level_music = "connemara";
    runningTimer = new Timer(_arduboy);
    beerSprite = new BeerSprite(_arduboy);
    speedFactor = (1.0 / (((int)speed + 0.5) / 2.0));
    startDuration = 1.0 * speedFactor;
    runningDuration = 7.5 * speedFactor;
    endDuration = 1.5 * speedFactor;
    percentage = 1;
}

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed) : Beer(arduboy, speed, 0) {}

void Beer::newBeer()
{
    currentBeerState = BeerState::FULL;
    currentBeerSips = 0;
    beerSprite->reset();
}

void Beer::setup()
{
    Stage::setup();
    newBeer();
    beerSprite->y = 25;
    beerSprite->x = -30;
    setStatus(StageStatus::STARTING);
}

void Beer::startingLoop()
{
    if (beerSprite->x < 30)
    {
        if (_arduboy->everyXFrames(ceil((startDuration / 1.5) * _arduboy->getFrameRate()) / 60))
        {
            beerSprite->x++;
        }
    }
    else
    {
        _arduboy->setCursor(95, 45);
        _arduboy->print(runningDuration);
        _arduboy->println("s");
    }
    
    if(_arduboy->everyXFrames(round((startDuration/160) * _arduboy->getFrameRate()))) {
        percentage++;
        _arduboy->fillRect(0, 55, ceil(160*(percentage/100)), 9, WHITE);
    }

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(startDuration);
    }

    if (runningTimer->isElapsed())
    {
        runningTimer->stop();
        beerSprite->x = 30;
        setStatus(StageStatus::RUNNING);
    }

    runningTimer->tick();

    _arduboy->setCursor(3, 0);
    _arduboy->println("Bois un max de bieres !");

    beerSprite->draw();
    _arduboy->display(CLEAR_BUFFER);
}

void Beer::runningLoop()
{
    if (_arduboy->justReleased(A_BUTTON) || _arduboy->justReleased(B_BUTTON))
        currentBeerSips++;

    BeerState state = (BeerState)currentBeerSips;

    if (state != currentBeerState)
    {
        currentBeerState = state;
        beerSprite->state = state;

        // glouglou sound

        if (state == BeerState::RESET)
        {
            newBeer();
            score++;
        }
    }

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(runningDuration);
    }

    if (runningTimer->isElapsed())
    {
        runningTimer->stop();
        setStatus(StageStatus::ENDING);
    }

    _arduboy->setCursor(3, 0);
    _arduboy->println("Bois un max de bieres !");
    _arduboy->setCursor(85 - ((score > 9 ? 2 : score > 1 ? 1 : 0) * 5), 35);
    _arduboy->print(score);
    _arduboy->print(" " + (score > 1 ? score_label : score_label_singular));
    _arduboy->setCursor(95, 45);
    _arduboy->print(runningTimer->timeOutSec - runningTimer->timeElapsed());
    _arduboy->println("s");

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
        runningTimer->setTimeout(endDuration);
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
