#include "Hand.h"

Hand::Hand(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    level_music = Music::FEDER;

    goalSprite = new GoalSprite(_arduboy);
    quicheSprite = new QuicheSprite(_arduboy);
    ballSprite = new BallSprite(_arduboy);

    speedFactor = 1.0 / sqrt((double)speed);
    startDuration = 2.0 * speedFactor;
    runningDuration = round(3.0 * speedFactor);
    endDuration = 1.5 * speedFactor;

    _arduboy->initRandomSeed();
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
}

void Hand::setup()
{
    Stage::setup();

    goPosition.x = 0;
    goPosition.y = 50;

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
        transition((startDuration * 0.50), 60, 10, -1, goalSprite->position.y);
        goalSprite->draw();
    }
    else
    {
        drawTimer(runningDuration);
        goalSprite->draw();
        quicheSprite->draw();
    }

    printInstructions();
}

void Hand::drawTimer(double time) {
    _arduboy->setCursor(95, 0);
    _arduboy->print(time);
    _arduboy->println("s");
}

void Hand::printInstructions() {
    _arduboy->setCursor(10, 0);
    _arduboy->println("GARDIENNE !");
    if (speed != StageSpeed::NORMAL)
    {
        _arduboy->setCursor(0, 10);
        _arduboy->println("vit.");
        _arduboy->print("  x");
        _arduboy->print((int)speed);
    }
}

void Hand::runningLoop()
{
    printInstructions();

    drawTimer(stageTimer->timeOutSec - stageTimer->timeElapsed());

    if (stageTimer->timeElapsed() >= (runningDuration/4.0))
    {
        if(
            (ballEndPosition.y > ballStartPosition.y && 
            ballSprite->position.y < ballEndPosition.y) ||
            (ballEndPosition.y < ballStartPosition.y && 
            ballSprite->position.y > ballEndPosition.y)
        ) {
            transition(
                (runningDuration/2.0), 
                abs(ballStartPosition.y - ballEndPosition.y), 
                ballEndPosition.y, 
                ballEndPosition.y > ballStartPosition.y ? 1 : -1, 
                ballSprite->position.y
            );
        }
    }

    if (stageTimer->timeElapsed() >= (runningDuration/4.0)) {
        if(ballSprite->size > 1) {

            transition(
                (runningDuration/2.0),
                10,
                1,
                -1,
                ballSprite->size
            );
        }
    }

    if (stageTimer->timeElapsed() >= (runningDuration/4.0)) {
        if (
            ballDirection == Direction::LEFT 
            ? (ballSprite->position.x < ballEndPosition.x) 
            : (ballSprite->position.x > ballEndPosition.x)
        ) {
            transition(
                (runningDuration/2.0),
                abs(ballStartPosition.x - ballEndPosition.x),
                ballEndPosition.x,
                (ballDirection == Direction::RIGHT ? -1 : 1),
                ballSprite->position.x
            );
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

    goalSprite->draw();
    quicheSprite->draw();
    ballSprite->draw();
}

void Hand::endingLoop()
{

    if (!stageTimer->isRunning())
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
    }

    _arduboy->setCursor(40, 0);
    _arduboy->print(score ? "EXCELLENT" : "  PERDU  ");

    goalSprite->draw();
    quicheSprite->draw();
    ballSprite->draw();
}