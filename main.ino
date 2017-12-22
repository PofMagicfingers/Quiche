/***************************************************************
Play a musical composition in the background while
the main sketch code runs in the foreground.

The ArduboyPlaytune library must be installed to use this sketch
https://github.com/Arduboy/ArduboyPlayTune

The D-Pad buttons will move the text and play a tone.

The A button mutes the sound.
The screen is inverted when sound is muted.

The B button will turn sound back on if it's muted.

The score that is played contains two parts.
With the DevKit only one part is played.
***************************************************************/

#include <Arduboy2.h>
Arduboy2 *arduboy = new Arduboy2();

#include "src/stages/Stage.h"
#include "src/stages/Hand/Hand.h"
#include "src/stages/Beer/Beer.h"

Stage *currentStage;
BoomBox *boomBox = new BoomBox();

int stageDone = 0;

enum class GameStatus
{
  BOOTING = 0,
  MENU,
  PLAYING,
  GAMEOVER,
  SCOREBOARD
};

GameStatus game_status = GameStatus::MENU;

void setup()
{
  arduboy->boot();

  arduboy->setFrameRate(60);
  arduboy->setTextSize(1);

  arduboy->audio.on();
  boomBox->setup(arduboy);
}

void loop()
{
  switch (game_status)
  {
  case GameStatus::MENU:
    menu();
    break;
  case GameStatus::PLAYING:
    playing();
    break;
  }
}

int quichy = -50;
bool playedBootSound = false;

int showStartText = 0;
void menu()
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

  if (arduboy->justReleased(A_BUTTON) || arduboy->justReleased(B_BUTTON))
  {
    game_status = GameStatus::PLAYING;
  }

  arduboy->display(CLEAR_BUFFER);
}

int num = 0;

void playing()
{
  if (currentStage && currentStage->isFinished())
  {
    stageDone++;
    delete currentStage;
    currentStage = NULL;
  }

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

    if(randed < 26 || stageDone == 0) {
      currentStage = new Hand(
          arduboy,
          stageSpeed,
          boomBox);
    }

    if(randed > 25 || stageDone == 1) {
      currentStage = new Beer(
          arduboy,
          stageSpeed,
          boomBox);
    }

    currentStage->setup();
  }

  if(currentStage) {
    currentStage->loop();
  }
}