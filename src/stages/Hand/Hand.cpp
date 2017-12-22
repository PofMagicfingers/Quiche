#include "Hand.h"

Hand::Hand(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    score_label_singular = "arret";
    score_label = "arrets";
    level_music = "feder";
    runningTimer = new Timer(_arduboy);

    goalSprite = new GoalSprite(_arduboy);
    quicheSprite = new QuicheSprite(_arduboy);
    ballSprite = new BallSprite(_arduboy);

    speedFactor = 1.0 / sqrt((double)speed);
    startDuration = 2.0 * speedFactor;
    runningDuration = round(30.0 * speedFactor);
    endDuration = 1.5 * speedFactor;

    percentage = 1;
}

Hand::~Hand()
{
    delete goalSprite;
    delete quicheSprite;
    delete ballSprite;
    delete runningTimer;
}

void Hand::setup()
{
    Stage::setup();
    goalSprite->position.y = 70;
    goalSprite->position.x = 30;

    quicheSprite->position.y = 25;
    quicheSprite->position.x = 45;

    setStatus(StageStatus::STARTING);
}

void Hand::startingLoop()
{
    if (goalSprite->position.y > 10)
    {
        int frameDelta = max(1, round(((startDuration * 0.50) * _arduboy->getFrameRate()) / 60));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                goalSprite->position.y = goalSprite->position.y - ceil(60 / ((startDuration * 0.50) * _arduboy->getFrameRate()));
            }
            else
            {
                goalSprite->position.y--;
            }
        }

        goalSprite->draw();
    }
    else
    {
        _arduboy->setCursor(95, 0);
        _arduboy->print(runningDuration);
        _arduboy->println("s");
        goalSprite->draw();
        quicheSprite->draw();
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

    _arduboy->fillRect(0, 60, ceil(WIDTH * (percentage / 100.0)), 4, WHITE);

    if (!runningTimer->isRunning())
    {
        runningTimer->reset();
        runningTimer->setTimeout(startDuration);
    }

    if (runningTimer->isElapsed())
    {
        runningTimer->stop();
        setStatus(StageStatus::RUNNING);
    }

    runningTimer->tick();

    _arduboy->setCursor(10, 0);
    _arduboy->println("GARDIENNE !");
    if (speed != StageSpeed::NORMAL)
    {
        _arduboy->setCursor(5, 10);
        _arduboy->print("vit. x");
        _arduboy->print((int)speed);
    }

    _arduboy->display(CLEAR_BUFFER);
}

void Hand::runningLoop()
{
    _arduboy->setCursor(10, 0);
    _arduboy->println("GARDIENNE !");
    if (speed != StageSpeed::NORMAL)
    {
        _arduboy->setCursor(5, 10);
        _arduboy->print("vit. x");
        _arduboy->print((int)speed);
    }

    if (_arduboy->everyXFrames(round(_arduboy->getFrameRate() * 0.6 * speedFactor)))
    {
        showGo = !showGo;
    }

    if (showGo)
    {
        _arduboy->setCursor(0, 20);
        _arduboy->println("GO !");
    }

    _arduboy->setCursor(95, 0);
    _arduboy->print(runningTimer->timeOutSec - runningTimer->timeElapsed());
    _arduboy->println("s");

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

    _arduboy->fillRect(0, 60, ceil(WIDTH * (percentage / 100.0)), 4, WHITE);

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

    if (
        _arduboy->notPressed(UP_BUTTON) &&
        _arduboy->notPressed(DOWN_BUTTON) &&
        _arduboy->notPressed(LEFT_BUTTON) &&
        _arduboy->notPressed(RIGHT_BUTTON) &&
        _arduboy->notPressed(A_BUTTON) &&
        _arduboy->notPressed(B_BUTTON)
    ) {
        quicheSprite->direction = Direction::NONE;
    }

    if (_arduboy->pressed(UP_BUTTON) || _arduboy->pressed(A_BUTTON) || _arduboy->pressed(B_BUTTON))
    {
        quicheSprite->direction = Direction::UP;
    }
    else if (_arduboy->pressed(LEFT_BUTTON))
    {
        quicheSprite->direction = Direction::LEFT;
    }
    else if (_arduboy->pressed(RIGHT_BUTTON))
    {
        quicheSprite->direction = Direction::RIGHT;
    }
    else if (_arduboy->pressed(DOWN_BUTTON))
    {
        quicheSprite->direction = Direction::DOWN;
    }

    goalSprite->draw();
    quicheSprite->draw();

    _arduboy->display(CLEAR_BUFFER);
}

void Hand::endingLoop()
{
    _arduboy->setCursor(0, 0);

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

    goalSprite->draw();

    _arduboy->display(CLEAR_BUFFER);
}

void Hand::wrapUp()
{
    _arduboy->display(CLEAR_BUFFER);
    Stage::wrapUp();
}
