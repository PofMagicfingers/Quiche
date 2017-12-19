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
}

void Stage::loop() {
    if ((*_arduboy).nextFrame()) {
        (*_arduboy).setCursor(0,0);
        (*_arduboy).println("looping");
        (*_arduboy).display(true);
//        (*_arduboy).pollButtons();

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
}

void Stage::wrapUp()
{
    if(boomBox.isPlaying())
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