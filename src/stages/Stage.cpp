#include "Stage.h"

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed) : 
_arduboy(arduboy), speed(speed) {
}

void Stage::setup()
{
    boomBox.setup(_arduboy);    
    score = 0;
    score_label = "points";
    finished = false;
    stageStatus = StageStatus::STARTING;
}

void Stage::loop() {
    if (!(*_arduboy).nextFrame()) {
        return;
    }
    (*_arduboy).pollButtons();

    switch(stageStatus) {
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

void Stage::startingLoop()
{
    boomBox.play(level_music);
}

void Stage::runningLoop()
{
}

void Stage::endingLoop()
{
}

void Stage::wrapUp()
{
    stageStatus = StageStatus::ENDING;
}

bool Stage::isFinished()
{
    return finished;

}

int Stage::getScore()
{
    return score;
}

String Stage::getScoreLabel()
{
    return score_label;
}