#include "Stage.h"

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : _arduboy(arduboy), speed(speed), boomBox(bbox)
{
    score.stageDone = 0;
    score.ballsStopped = 0;
    score.beersDrunk = 0;
    finished = false;
    stageStatus = StageStatus::SETUP;
    stageTimer = new Timer(_arduboy);
}

Stage::~Stage()
{
    delete stageTimer;
}

void Stage::setup()
{
    switch (speed)
    {
    case StageSpeed::NORMAL:
        boomBox->setSpeed(1.0);
        break;
    case StageSpeed::SPEEDY:
        boomBox->setSpeed(1.5);
        break;
    case StageSpeed::FAST:
        boomBox->setSpeed(2.0);
        break;
    case StageSpeed::INSANE:
        boomBox->setSpeed(2.25);
        break;
    }
    boomBox->play(level_music);
}

void Stage::loop()
{
    if (!_arduboy->nextFrame())
        return;

    _arduboy->pollButtons();

    switch (stageStatus)
    {
    case StageStatus::STARTING:
        startingLoop();

        transition(startDuration, 100, 100, 1, percentage);
        _arduboy->fillRect(0, 60, ceil(WIDTH * (percentage / 100.0)), 4, WHITE);

        if (!stageTimer->isRunning())
        {
            stageTimer->reset();
            stageTimer->setTimeout(startDuration);
        }

        if (stageTimer->isElapsed())
        {
            stageTimer->stop();
            setStatus(StageStatus::RUNNING);
        }

        stageTimer->tick();
        break;
    case StageStatus::RUNNING:
        runningLoop();

        if (_arduboy->everyXFrames(round(_arduboy->getFrameRate() * 0.6 * speedFactor)))
        {
            showGo = !showGo;
        }

        if (showGo)
        {
            _arduboy->setCursor(goPosition.x, goPosition.y);
            _arduboy->println("GO !");
        }

        transition(runningDuration, 100, 0, -1, percentage);
        _arduboy->fillRect(0, 60, ceil(WIDTH * (percentage / 100.0)), 4, WHITE);

        if (!stageTimer->isRunning())
        {
            stageTimer->reset();
            stageTimer->setTimeout(runningDuration);
        }

        if (stageTimer->isElapsed())
        {
            stageTimer->stop();
            setStatus(StageStatus::ENDING);
        }

        stageTimer->tick();
        break;
        
    case StageStatus::ENDING:
        endingLoop();
        if (!stageTimer->isRunning())
        {
            stageTimer->reset();
            stageTimer->setTimeout(endDuration);
        }

        if (stageTimer->isElapsed())
        {
            wrapUp();
        }
        stageTimer->tick();
        break;
    }

    _arduboy->display(CLEAR_BUFFER);
}

void Stage::wrapUp()
{
    boomBox->stop();
    finished = true;
}

bool Stage::isFinished()
{
    return finished;
}

StageScore Stage::getScore()
{
    return score;
}

void Stage::setStatus(StageStatus newStatus)
{
    stageStatus = newStatus;
}

void Stage::transition(float duration, int delta,
                       int goal, int direction, int &attr)
{
    int frameDelta = max(1, round((duration * _arduboy->getFrameRate()) / delta));
    if (_arduboy->everyXFrames(frameDelta))
    {
        if (
            (direction == 1 && attr >= goal) || 
            (direction == -1 && attr <= goal)
        )
        {
            attr = goal;
        }
        else
        {
            if (frameDelta == 1)
            {
                attr = attr + direction * ceil(delta / (duration * _arduboy->getFrameRate()));
            }
            else
            {
                attr = attr + direction;
            }
        }
    }
}