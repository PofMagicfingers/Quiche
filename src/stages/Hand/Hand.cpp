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
    runningDuration = round(3.0 * speedFactor);
    endDuration = 1.5 * speedFactor;

    percentage = 1;

    randomSeed(analogRead(A0));
    int randed = random(0, 40);
    if(randed > 30) {
        ballDirection = Direction::UP;
    } else if(randed > 20) {
        ballDirection = Direction::RIGHT;
    } else if(randed > 10) {
        ballDirection = Direction::LEFT;
    } else if(randed > 0) {
        ballDirection = Direction::DOWN;
    }

    switch (ballDirection) {
        case Direction::LEFT:
            ballStartPosition.x = -60;
            ballStartPosition.y = 50;
            ballEndPosition.x = 20;
            ballEndPosition.y = 15;
            break;
        case Direction::RIGHT:
            ballStartPosition.x = 175;
            ballStartPosition.y = 50;
            ballEndPosition.x = 58;
            ballEndPosition.y = 15;
            break;
        case Direction::DOWN:
            ballStartPosition.x = 40;
            ballStartPosition.y = 64;
            ballEndPosition.x = 40;
            ballEndPosition.y = 20;
            break;
        case Direction::UP:
            ballStartPosition.x = 40;
            ballStartPosition.y = 64;
            ballEndPosition.x = 35;
            ballEndPosition.y = -5;
            break;
    }

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

    ballSprite->position = ballStartPosition;

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
        _arduboy->setCursor(0, 10);
        _arduboy->println("vit.");
        _arduboy->print("  x");
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
        _arduboy->setCursor(0, 10);
        _arduboy->println("vit.");
        _arduboy->print("  x");
        _arduboy->print((int)speed);
    }


    if (_arduboy->everyXFrames(round(_arduboy->getFrameRate() * 0.6 * speedFactor)))
    {
        showGo = !showGo;
    }

    if (showGo)
    {
        _arduboy->setCursor(0, 50);
        _arduboy->println("GO !");
    }

    _arduboy->setCursor(95, 0);
    _arduboy->print(runningTimer->timeOutSec - runningTimer->timeElapsed());
    _arduboy->println("s");

    if (runningTimer->timeElapsed() >= (runningDuration/4.0) && ballSprite->position.y > ballEndPosition.y)
    {
        int frameDelta = max(1, round(((runningDuration/2.0) * _arduboy->getFrameRate()) / abs(ballStartPosition.y - ballEndPosition.y) ));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                ballSprite->position.y = ballSprite->position.y - ceil(abs(ballStartPosition.y - ballEndPosition.y) / ((runningDuration/2.0) * _arduboy->getFrameRate()));
            }
            else
            {
                ballSprite->position.y--;
            }
        }
    }

    if (runningTimer->timeElapsed() >= (runningDuration/4.0) && ballSprite->size > 1)
    {
        int frameDelta = max(1, round(((runningDuration/2.0) * _arduboy->getFrameRate()) / 10 ));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                ballSprite->size = ballSprite->size - ceil(10 / ((runningDuration/2.0) * _arduboy->getFrameRate()));
            }
            else
            {
                ballSprite->size--;
            }
        }
    }

    if (runningTimer->timeElapsed() >= (runningDuration/4.0) && (ballDirection == Direction::LEFT ? (ballSprite->position.x < ballEndPosition.x) : (ballSprite->position.x > ballEndPosition.x)))
    {
        int frameDelta = max(1, round(((runningDuration/2.0) * _arduboy->getFrameRate()) / abs(ballStartPosition.x - ballEndPosition.x) ));
        if (_arduboy->everyXFrames(frameDelta))
        {
            if (frameDelta == 1)
            {
                ballSprite->position.x = ballSprite->position.x + ((ballDirection == Direction::RIGHT ? -1 : 1)*ceil(abs(ballStartPosition.x - ballEndPosition.x) / ((runningDuration/2.0) * _arduboy->getFrameRate())));
            }
            else
            {
                ballSprite->position.x = ballSprite->position.x + (ballDirection == Direction::RIGHT ? -1 : 1);
            }
        }
    }

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

    goalSprite->draw();
    quicheSprite->draw();
    ballSprite->draw();

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

    _arduboy->display(CLEAR_BUFFER);
}

void Hand::endingLoop()
{

    if (!runningTimer->isRunning())
    {
        if(ballDirection == quicheSprite->direction) {
            score++;
            boomBox->tunes->tone(440, 100);
            _arduboy->delayShort(100);
            boomBox->tunes->tone(1540, 600);
        } else {
            boomBox->tunes->tone(1440, 100);
            _arduboy->delayShort(100);
            boomBox->tunes->tone(200, 600);
        }

        runningTimer->reset();
        runningTimer->setTimeout(endDuration);
    }

    _arduboy->setCursor(40, 0);
    _arduboy->print(score ? "EXCELLENT" : "  PERDU  ");

    goalSprite->draw();
    quicheSprite->draw();
    ballSprite->draw();

    _arduboy->display(CLEAR_BUFFER);

    if (runningTimer->isElapsed())
    {
        wrapUp();
    } else {
        runningTimer->tick();
    }
}

void Hand::wrapUp()
{
    _arduboy->display(CLEAR_BUFFER);
    Stage::wrapUp();
}
