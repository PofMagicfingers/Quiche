#include "Stage.h"

using namespace std;

Stage::Stage(Arduboy2 *arduboy, StageSpeed speed) {
    _arduboy = arduboy;
    speed = speed;
}

virtual void Stage::setup()
{
    score = 0;
    score_label = "points";
    finished = false;
    stageStatus = StageStatus::STARTING;
}

virtual void Stage::loop() {
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
}

void Stage::runningLoop()
{
}

void Stage::endingLoop()
{
}

virtual void Stage::wrapUp()
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

string Stage::getScoreLabel()
{
    return score_label;
}