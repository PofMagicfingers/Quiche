#include "Game.h"

Game::Game()
{
    arduboy = new Arduboy2();
    boomBox = new BoomBox();
}

Game::~Game()
{
    delete arduboy;
    if(currentStage != NULL) {
        delete currentStage;
    }
}

void Game::setup() {
  stageDone = 0;
  arduboy->boot();

  arduboy->blank();
  arduboy->flashlight();
  arduboy->systemButtons();
  arduboy->audio.begin();

  arduboy->setFrameRate(50);
  arduboy->setTextSize(1);

  boomBox->setup(arduboy);
}

void Game::loop() {
  switch (game_status)
  {
  case GameStatus::MENU:
    menu();
    break;
  case GameStatus::GAMEOVER:
    gameover();
    break;
  case GameStatus::PLAYING:
    playing();
    break;
  }
}

void Game::menu() 
{
  if (!arduboy->nextFrame())
    return;

  arduboy->pollButtons();

  arduboy->setTextSize(3);
  arduboy->setCursor(12, quichy);
  arduboy->println("QUICHE");
  arduboy->setTextSize(1);

  if (quichy < 15)
  {
    if (quichy == -50)
    {
      arduboy->digitalWriteRGB(RED_LED, RGB_ON);
    }

    if (quichy == -30)
    {
      arduboy->digitalWriteRGB(RED_LED, RGB_OFF);  // red LED off
      arduboy->digitalWriteRGB(GREEN_LED, RGB_ON); // green LED on
    }

    if (quichy == -10)
    {
      arduboy->digitalWriteRGB(GREEN_LED, RGB_OFF); // green LED off
      arduboy->digitalWriteRGB(BLUE_LED, RGB_ON);   // blue LED on
    }

    if (quichy == 10)
    {
      arduboy->digitalWriteRGB(BLUE_LED, RGB_OFF);
    }

    if (arduboy->everyXFrames(3))
    {
      quichy++;
    }
  }
  else if (quichy == 16)
  {
    quichy++;
  }
  else
  {
    if (!playedBootSound)
    {
      boomBox->tunes->tone(1046, 100);
      arduboy->delayShort(90);
      boomBox->tunes->tone(2093, 500);

      playedBootSound = true;
    }

    if (arduboy->everyXFrames(arduboy->getFrameRate() / 2))
    {
      showStartText++;
    }
    if (showStartText > 0)
    {
      arduboy->setCursor(12, 50);
      arduboy->println("A/B pour commencer");
      if (showStartText >= 3)
      {
        if (!boomBox->isPlaying())
          boomBox->playRandom();
        showStartText = 0;
      }
    }
  }

  if (playedBootSound && (arduboy->justReleased(A_BUTTON) || arduboy->justReleased(B_BUTTON)))
  {
    stageDone = 0;
    game_status = GameStatus::PLAYING;
  }

  if (arduboy->pressed(RIGHT_BUTTON))
  {
    arduboy->digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
  }

  arduboy->display(CLEAR_BUFFER);
}

void Game::gameover()
{
  if (!arduboy->nextFrame())
    return;

  arduboy->clear();
  arduboy->setTextSize(2);
  arduboy->setCursor(13, 20);
  arduboy->println("GAME OVER");
  arduboy->setTextSize(1);
  arduboy->setCursor(stageDone > 10 ? 9 : stageDone > 1 ? 13 : 20, 40);
  arduboy->print(stageDone);
  if (stageDone > 1)
  {
    arduboy->println(" niveaux gagnants");
  }
  else
  {
    arduboy->println(" niveau gagnant");
  }

  arduboy->display(CLEAR_BUFFER);

  arduboy->pollButtons();
  if (arduboy->justReleased(A_BUTTON) || arduboy->justReleased(B_BUTTON))
  {
    game_status = GameStatus::MENU;
  }
}

void Game::playing()
{
  if (!currentStage)
  {

    StageSpeed stageSpeed = StageSpeed::NORMAL;

    if (stageDone > 3)
    {
      stageSpeed = StageSpeed::SPEEDY;
    }

    if (stageDone > 7)
    {
      stageSpeed = StageSpeed::FAST;
    }

    if (stageDone > 10)
    {
      stageSpeed = StageSpeed::INSANE;
    }

    int randed = random(0, 50);

    if (stageDone == 0 || stageDone > 1 && randed < 26)
    {
      currentStage = new Hand(
          arduboy,
          stageSpeed,
          boomBox);
    }
    else if (stageDone == 1 || stageDone > 1 && randed > 25)
    {
      currentStage = new Beer(
          arduboy,
          stageSpeed,
          boomBox);
    }

    currentStage->setup();
  }

  if (currentStage)
  {
    arduboy->clear();
    currentStage->loop();
  }

  if (currentStage->isFinished())
  {
    if (currentStage->getScore() == 0)
    {
      game_status = GameStatus::GAMEOVER;
    }
    else
    {
      stageDone++;
    }
    delete currentStage;
    currentStage = NULL;
  }
}