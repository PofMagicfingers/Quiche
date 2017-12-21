#include "Beer.h"

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    score_label_singular = "biere";
    score_label = "bieres";
    level_music = "connemara";
    runningTimer = new Timer(_arduboy);
    beerSprite = new BeerSprite(_arduboy);
    speedFactor = 1.0/sqrt((double)speed);
    startDuration = 1.0 * speedFactor;
    runningDuration = round(8.0 * speedFactor);
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
        int frameDelta = max(1, round(((startDuration * 0.75) * _arduboy->getFrameRate()) / 60));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                beerSprite->x = beerSprite->x + ceil(60 / ((startDuration * 0.75) * _arduboy->getFrameRate()));
            }
            else
            {
                beerSprite->x++;
            }
        }
    }
    else
    {
        _arduboy->setCursor(95, 45);
        _arduboy->print(runningDuration);
        _arduboy->println("s");

        _arduboy->setCursor(85, 35);
        _arduboy->print("0 " + score_label_singular);    
    }

    int frameDelta = max(1, round((startDuration * _arduboy->getFrameRate()) / 100));
    if (_arduboy->everyXFrames(frameDelta))
    {
        if (percentage >= 99)
        {
            percentage = 100;
        }
        else
        {
            if (frameDelta == 1)
            {
                percentage = percentage + ceil(100 / (startDuration * _arduboy->getFrameRate()));
            }
            else
            {
                percentage++;
            }
        }
    }

    _arduboy->fillRect(0, 58, ceil(WIDTH * (percentage / 100.0)), 6, WHITE);

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
    if(speed != StageSpeed::NORMAL) {
        _arduboy->setCursor(5, 10);
        _arduboy->print("vit. x");
        _arduboy->print((int)speed);
    }

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

    _arduboy->setCursor(3, 0);
    _arduboy->println("Bois un max de bieres !");
    if(speed != StageSpeed::NORMAL) {
        _arduboy->setCursor(5, 10);
        _arduboy->print("vit. x");
        _arduboy->print((int)speed);
    }

    if(_arduboy->everyXFrames(round(_arduboy->getFrameRate()*0.6*speedFactor))) {
        showGo = !showGo;
    }

    if(showGo) {
        _arduboy->setCursor(100, 20);
        _arduboy->println("GO !");
    }

    scorePosition.x = 85 - ((score > 9 ? 2 : score > 1 ? 1 : 0) * 5);
    scorePosition.y = 35;
    _arduboy->setCursor(scorePosition.x, scorePosition.y);

    _arduboy->print(score);
    _arduboy->print(" " + (score > 1 ? score_label : score_label_singular));

    _arduboy->setCursor(95, 45);
    _arduboy->print(runningTimer->timeOutSec - runningTimer->timeElapsed());
    _arduboy->println("s");

    beerSprite->draw();

    int frameDelta = max(1, round((runningDuration * _arduboy->getFrameRate()) / 100));
    if (_arduboy->everyXFrames(frameDelta))
    {
        if (percentage <= 1)
        {
            percentage = 0;
        }
        else
        {
            if (frameDelta == 1)
            {
                percentage = percentage - ceil(100 / (runningDuration * _arduboy->getFrameRate()));
            }
            else
            {
                percentage--;
            }
        }
    }

    _arduboy->fillRect(0, 58, ceil(WIDTH * (percentage / 100.0)), 6, WHITE);

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

    runningTimer->tick();
    _arduboy->display(CLEAR_BUFFER);
}

void Beer::endingLoop()
{
    _arduboy->setCursor(0, 0);


    if (beerSprite->y < 70)
    {
        int frameDelta = max(1, round(((startDuration * 0.75) * _arduboy->getFrameRate()) / 45));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                beerSprite->y = beerSprite->y + ceil(45 / ((startDuration * 0.75) * _arduboy->getFrameRate()));
            }
            else
            {
                beerSprite->y++;
            }
        }
    }

    int scoreDestX = round(
        (
            WIDTH - 5 -
            (
                (score > 10 ? 6.5 : 0) + 
                (
                    score > 1 ? 
                    sizeof(score_label) : 
                    sizeof(score_label_singular)
                ) * 6.5
            )
        ) / 2
    );

    if (scorePosition.x > scoreDestX)
    {
        int frameDelta = max(1, round(((endDuration * 0.75) * _arduboy->getFrameRate()) / (85-scoreDestX)));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                scorePosition.x = scorePosition.x - abs(ceil((85-scoreDestX) / ((endDuration * 0.75) * _arduboy->getFrameRate())));
            }
            else
            {
                scorePosition.x--;
            }
        }
    }

    if (scorePosition.y > 30)
    {
        int frameDelta = max(1, round(((endDuration * 0.5) * _arduboy->getFrameRate()) / 5));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                scorePosition.y = scorePosition.y + abs(ceil(5 / ((endDuration * 0.5) * _arduboy->getFrameRate())));
            }
            else
            {
                scorePosition.y--;
            }
        }
    }

    _arduboy->setCursor(scorePosition.x, scorePosition.y);
    _arduboy->print(score);
    _arduboy->print(" " + (score > 1 ? score_label : score_label_singular));

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

    beerSprite->draw();
    _arduboy->display(CLEAR_BUFFER);    
}

void Beer::wrapUp()
{
    _arduboy->display(CLEAR_BUFFER);
    Stage::wrapUp();
}
