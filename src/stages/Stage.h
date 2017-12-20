#ifndef Stage_h
#define Stage_h

#include <Arduboy2.h>
#include "../BoomBox.h"

enum class StageSpeed
{
    NORMAL,
    SPEEDY,
    FAST,
    INSANE
};

enum class StageStatus
{
    SETUP,
    STARTING,
    RUNNING,
    ENDING
};

class Stage
{
  public:
    Stage(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox);
    Stage(Arduboy2 *arbuboy, StageSpeed speed);
    virtual void setup();
    virtual void loop();
    virtual void wrapUp();
    bool isFinished();
    int getScore();
    String getScoreLabel();

  protected:
    virtual void startingLoop() = 0;
    virtual void runningLoop() = 0;
    virtual void endingLoop() = 0;
    void setStatus(StageStatus);

    Arduboy2 *_arduboy;
    String score_label;
    String score_label_singular;
    String level_music;
    int score;
    bool finished;
    StageSpeed speed;
    BoomBox *boomBox;

  private:
    StageStatus stageStatus;
};

#endif