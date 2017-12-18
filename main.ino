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

#include "lib/Arduboy2/src/Arduboy2.h"
#include "src/BoomBox.h"

BoomBox boomBox;
Arduboy2 arduboy;
void setup()
{
  arduboy.boot();

  arduboy.setFrameRate(25);
  arduboy.setTextSize(1);

  boomBox.setup();

  arduboy.audio.off();
  arduboy.invert(!arduboy.audio.enabled()); // invert display if sound muted
}

float speed = 1.0;

void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  if (arduboy.pressed(UP_BUTTON)) {
    if(speed < 5) { speed = speed + 0.1; }
    //tunes.scorePlaybackSpeed(speed);
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    if(speed > 0.1) { speed = speed - 0.1; }
    //tunes.scorePlaybackSpeed(speed);
  }

  if (arduboy.pressed(A_BUTTON)) {
    if(arduboy.audio.enabled()) {
      arduboy.invert(true);
      arduboy.audio.off();
    } else {
      arduboy.invert(false);
      arduboy.audio.on();
    }
  } else if (arduboy.pressed(B_BUTTON)) {
    //tunes.stopScore();
    speed = 1.0;
  }

  arduboy.clear();
  arduboy.setCursor(5,5);
  arduboy.print("Current speed: ");
  arduboy.print(speed);
  arduboy.setCursor(5,20);
  arduboy.print("Muted: ");
  arduboy.print(arduboy.audio.enabled() ? "NO" : "YES");
  arduboy.display();

  // play the tune if we aren't already
  // if (!tunes.playing()) {
  //   tunes.scorePlaybackSpeed(speed);
  //   tunes.playScore(score);
  // }
}