#ifndef Stage_h
#define Stage_h

#include <Arduboy2.h>
#include "../BoomBox.h"
#include "../Timer.h"


struct StageScore {
    int stageDone = 0;
    int beersDrunk = 0;
    int ballsStopped = 0;
};

enum class StageSpeed
{
    NORMAL = 1,
    SPEEDY,
    FAST,
    INSANE
};

enum class StageStatus
{
    SETUP = 1,
    STARTING,
    RUNNING,
    ENDING
};

class Stage
{
  public:
    Stage(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox);
    ~Stage();
    virtual void setup();
    virtual void loop();
    virtual void wrapUp();
    bool isFinished();
    StageScore getScore();

  protected:
    virtual void startingLoop() = 0;
    virtual void runningLoop() = 0;
    virtual void endingLoop() = 0;
    void setStatus(StageStatus);

    void transition(float duration, int delta, int goal, int direction, int &attr);

    Arduboy2 *_arduboy;
    Music level_music;
    StageScore score;
    bool finished;

    double speedFactor;
    double startDuration;
    double runningDuration;
    double endDuration;

    Point goPosition;

    bool showGo = true;
    int percentage = 1;
    
    StageSpeed speed;
    BoomBox * boomBox;
    Timer * stageTimer;

  private:
    StageStatus stageStatus;
};

#endif