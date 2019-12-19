#ifndef GAMESINGLETON_H
#define GAMESINGLETON_H

#include <Arduboy2.h>

#include "src/stages/Stage.h"
#include "src/stages/Hand/Hand.h"
#include "src/stages/Beer/Beer.h"

enum class GameStatus
{
    BOOTING = 0,
    MENU,
    PLAYING,
    GAMEOVER,
    SCOREBOARD
};

class Game
{
  private:
    Game &operator=(const Game &) {}
    Game(const Game &) {}
    Game();
    ~Game();

  public:
    static Game *SharedInstance()
    {
        if (NULL == _singleton)
        {
            _singleton = new Game();
        }
        return _singleton;
    }
    static void kill()
    {
        if (NULL != _singleton)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }

    void setup();
    void loop();

  private:
    void menu();
    void gameover();
    void playing();

    void saveRecord();
    void printScores(StageScore score);

    static Game *_singleton;

    Arduboy2 *arduboy;
    Stage *currentStage;
    BoomBox *boomBox;
    StageScore recordScore;
    StageScore currentScore;
    GameStatus game_status = GameStatus::MENU;

    int quichy = -50;
    bool playedBootSound = false;
    int showStartText = 0;
};
#endif
