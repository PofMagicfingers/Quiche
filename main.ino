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
Arduboy2 * arduboy = new Arduboy2();

#include "src/stages/Stage.h"
#include "src/stages/Beer/Beer.h"

Stage * currentStage;
BoomBox * boomBox = new BoomBox();

int stageDone = 0;

enum class GameStatus {
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

  arduboy->audio.off();
  boomBox->setup(arduboy);
  boomBox->playRandom();
  
}

void loop()
{
  if(arduboy->nextFrame()) {
    switch(game_status) {
      case GameStatus::MENU:
        menu();
        break;
      case GameStatus::PLAYING:
        playing();
        break;
    }
  }
}

int showStartText = 0;
void menu() {
  arduboy->setTextSize(3);
  arduboy->setCursor(12, 15);
  arduboy->println("QUICHE");
  arduboy->setTextSize(1);

  if(arduboy->everyXFrames(arduboy->getFrameRate()/2)) {
    showStartText++;
  }
  if(showStartText > 0) {
    arduboy->setCursor(12, 50);
    arduboy->println("A/B pour commencer");
    if(showStartText >= 3) showStartText = 0;
  }
  arduboy->display(CLEAR_BUFFER);
}

void playing() {
  if(!currentStage) {
    
    StageSpeed stageSpeed = StageSpeed::NORMAL;

    if(stageDone > 3) {
      stageSpeed = StageSpeed::SPEEDY;
    }

    if(stageDone > 7) {
      stageSpeed = StageSpeed::FAST;
    }

    if(stageDone > 10) {
      stageSpeed = StageSpeed::INSANE;
    }

    currentStage = new Beer(
      arduboy, 
      stageSpeed, 
      boomBox
    );
    currentStage->setup();
  }

  if(currentStage->isFinished()) {
    delete currentStage;
    currentStage = NULL;
    stageDone++;
  } else {
    currentStage->loop();    
  }
}