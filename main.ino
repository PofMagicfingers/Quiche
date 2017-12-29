#include "Game.h"

Game *game = Game::SharedInstance();

void setup()
{
  game->setup();
}

void loop()
{
  game->loop();
}