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

void setup()
{
  arduboy->boot();

  arduboy->setFrameRate(25);
  arduboy->setTextSize(1);

  arduboy->audio.on();
  boomBox->setup(arduboy);
  // boomBox->playRandom();
}

void loop()
{
  if(!currentStage) {
    currentStage = new Beer(arduboy, StageSpeed::SLOW, boomBox);
    currentStage->setup();
  }

  if(currentStage->isFinished()) {
    arduboy->setCursor(0,0);
    arduboy->println("FINITOTO!");
    arduboy->display(true);
  } else {
    currentStage->loop();    
  }
}