#include "Stage.h"

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : _arduboy(arduboy), speed(speed), boomBox(bbox)
{
    score = 0;
    score_label = "points";
    finished = false;
    level_music = "none";
    stageStatus = StageStatus::SETUP;
}

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed) : Stage(arduboy, speed, 0) {}

void Stage::setup()
{
    if (!boomBox)
    {
        boomBox = new BoomBox();
    }
    boomBox->setup(_arduboy);

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
        break;
    case StageStatus::RUNNING:
        runningLoop();
        break;
    case StageStatus::ENDING:
        endingLoop();
        break;
    }
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

int Stage::getScore()
{
    return score;
}

void Stage::setStatus(StageStatus newStatus)
{
    stageStatus = newStatus;
}

String Stage::getScoreLabel()
{
    return score_label;
}