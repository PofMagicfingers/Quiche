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
#include "src/stages/Stage.h"
#include "src/stages/Beer/Beer.h"

Arduboy2 arduboy;
Stage *currentStage(0);
Beer beerStage(&arduboy, StageSpeed::SLOW);

void setup()
{
  arduboy.begin();

  arduboy.setFrameRate(25);
  arduboy.setTextSize(1);

  arduboy.clear();
  arduboy.println("booting");
  arduboy.display(CLEAR_BUFFER);

  if(!currentStage) {
    currentStage = new Beer(&arduboy, StageSpeed::SLOW);
    currentStage->setup();
  }
}

void loop()
{
  currentStage->loop();    
}