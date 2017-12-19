#include "Stage.h"

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed) : 
_arduboy(arduboy), speed(speed) {
    score = 0;
    score_label = "points";
    finished = false;
    level_music = "none";
    stageStatus = StageStatus::SETUP;
}

void Stage::setup()
{
    boomBox.setup(_arduboy);    
    boomBox.play(level_music);
}

void Stage::loop() {
    if (!_arduboy->nextFrame()) return;
    
    _arduboy->pollButtons();

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
    boomBox.stop();
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

void Stage::setStatus(StageStatus newStatus) {
    stageStatus = newStatus;
}

String Stage::getScoreLabel()
{
    return score_label;
}