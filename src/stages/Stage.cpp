#include "Stage.h"

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed) : 
_arduboy(arduboy), speed(speed) {
}

void Stage::setup()
{
    boomBox.setup(_arduboy);    
    boomBox.play(level_music);
    score = 0;
    score_label = "points";
    finished = false;
    stageStatus = StageStatus::STARTING;
    _secElapsed = 0;
}

void Stage::loop() {
    if (!(*_arduboy).nextFrame()) {
        return;
    }
    (*_arduboy).pollButtons();

    if((*_arduboy).everyXFrames(25)) {
        _secElapsed++;
    }

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

void Stage::setStatus(StageStatus newStatus) {
    stageStatus = newStatus;
}

String Stage::getScoreLabel()
{
    return score_label;
}