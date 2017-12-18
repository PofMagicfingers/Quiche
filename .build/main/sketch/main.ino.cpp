#include <Arduino.h>
#line 1 "/home/pof/Documents/Code/perso/noel/main.ino"
#line 1 "/home/pof/Documents/Code/perso/noel/main.ino"
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
#include <ArduboyPlaytune.h>

const byte score[] PROGMEM = {
 0x90,58, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80,
 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217,
 0x80, 0,26, 0x90,63, 1,217, 0x80, 0,26, 0x90,63, 1,217, 0x80, 0,26, 0x90,58, 1,217, 0x80, 0,26, 0x90,60,
 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26, 0x90,60, 1,217, 0x80, 0,26,
 0x90,60, 1,217, 0x80, 0,26, 0x90,58, 1,217, 0x80, 0,26, 0x90,58, 1,217, 0x80, 0,26, 0x90,57, 1,217, 0x80,
 0,26, 0x90,57, 1,217, 0x80, 0,26, 0x90,57, 2,199, 0x80, 1,32, 0x90,60, 0,236, 0x80, 0,13, 0x90,60, 0,236,
 0x80, 0,13, 0x90,62, 0,236, 0x80, 0,13, 0x90,63, 0,236, 0x80, 0,13, 0x90,65, 0,236, 0x80, 0,13, 0x90,67,
 3,180, 0x80, 1,45, 0x90,72, 0,236, 0x80, 0,13, 0x90,72, 0,236, 0x80, 0,13, 0x90,70, 0,236, 0x80, 0,13,
 0x90,70, 0,236, 0x80, 0,13, 0x90,68, 2,199, 0x80, 3,20, 0x90,67, 1,99, 0x80, 0,19, 0x90,65, 0,117, 0x80,
 0,7, 0x90,63, 1,99, 0x80, 0,19, 0x90,65, 0,117, 0x80, 0,7, 0x90,67, 0,236, 0x80, 0,13, 0x90,65, 0,236,
 0x80, 0,13, 0x90,63, 0,236, 0x80, 0,13, 0x90,65, 0,236, 0x80, 0,13, 0x90,67, 0,236, 0x80, 0,13, 0x90,67,
 0,236, 0x80, 0,13, 0x90,60, 0,236, 0x80, 0,13, 0x90,60, 0,236, 0x80, 6,227, 0x90,45, 0x91,57, 2,199, 0x80,
 0x81, 0,38, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,45, 0x91,57,
 0,236, 0x80, 0x81, 0,13, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,44, 0x91,56, 0,117, 0x81, 0,7, 0x91,56,
 0,170, 0x80, 0,6, 0x81, 0,10, 0x90,44, 0x91,56, 0,117, 0x80, 0x81, 0,7, 0x90,44, 0x91,56, 0,117, 0x80, 0x81,
 0,7, 0x90,44, 0x91,56, 0,236, 0x80, 0x81, 0,13, 0x90,44, 0x91,56, 0,236, 0x80, 0x81, 0,13, 0x90,44, 0x91,56,
 0,58, 0x80, 0x81, 0,4, 0x90,45, 0x91,57, 1,217, 0x80, 0x81, 0,26, 0x90,38, 0x91,50, 3,180, 0x80, 0x81, 3,158,
 0x90,45, 0x91,57, 2,199, 0x80, 0x81, 0,38, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,45, 0x91,57, 0,236,
 0x80, 0x81, 0,13, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,45, 0x91,57, 0,236, 0x80, 0x81, 0,13, 0x90,44,
 0x91,56, 0,117, 0x81, 0,7, 0x91,56, 0,170, 0x80, 0,6, 0x81, 0,10, 0x90,44, 0x91,56, 0,117, 0x80, 0x81, 0,7,
 0x90,44, 0x91,56, 0,117, 0x80, 0x81, 0,7, 0x90,44, 0x91,56, 0,236, 0x80, 0x81, 0,13, 0x90,44, 0x91,56, 0,236,
 0x80, 0x81, 0,13, 0x90,44, 0x91,56, 0,58, 0x80, 0x81, 0,4, 0x90,45, 0x91,57, 1,217, 0x80, 0x81, 0,26, 0x90,38,
 0x91,50, 3,180, 0x80, 0x81, 7,134, 0x90,60, 0,236, 0x80, 0,13, 0x90,60, 0,236, 0x80, 0,13, 0x90,62, 0,236,
 0x80, 0,13, 0x90,63, 0,236, 0x80, 0,13, 0x90,65, 0,236, 0x80, 0,13, 0x90,67, 3,180, 0x80, 1,45, 0x90,72,
 0,236, 0x80, 0,13, 0x90,72, 0,236, 0x80, 0,13, 0x90,70, 0,236, 0x80, 0,13, 0x90,70, 0,236, 0x80, 0,13,
 0x90,68, 2,199, 0x80, 3,20, 0x90,67, 1,99, 0x80, 0,19, 0x90,65, 0,117, 0x80, 0,7, 0x90,63, 1,99, 0x80,
 0,19, 0x90,65, 0,117, 0x80, 0,7, 0x90,67, 0,236, 0x80, 0,13, 0x90,65, 0,236, 0x80, 0,13, 0x90,63, 0,236,
 0x80, 0,13, 0x90,65, 0,236, 0x80, 0,13, 0x90,67, 0,236, 0x80, 0,13, 0x90,67, 0,236, 0x80, 0,13, 0x90,60,
 0,236, 0x80, 0,13, 0x90,60, 0,236, 0x80,
 0xf0
};

Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);

#line 58 "/home/pof/Documents/Code/perso/noel/main.ino"
void setup();
#line 85 "/home/pof/Documents/Code/perso/noel/main.ino"
void loop();
#line 58 "/home/pof/Documents/Code/perso/noel/main.ino"
void setup()
{
  arduboy.begin();

  arduboy.setFrameRate(25);
  arduboy.setTextSize(1);

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
  // if not a DevKit
  tunes.initChannel(PIN_SPEAKER_2);
#else
  // if it's a DevKit
  tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
  tunes.toneMutesScore(true);       // mute the score when a tone is sounding
#endif
  tunes.toneMutesScore(true); 

  arduboy.audio.off();
  arduboy.invert(!arduboy.audio.enabled()); // invert display if sound muted
}


int x = 20, y = 10; // initial text position
float speed = 1.0;

void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  if (arduboy.pressed(UP_BUTTON)) {
    if(speed < 5) { speed = speed + 0.1; }
    tunes.scorePlaybackSpeed(speed);
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    if(speed > 0.1) { speed = speed - 0.1; }
    tunes.scorePlaybackSpeed(speed);
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
    tunes.stopScore();
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
  if (!tunes.playing()) {
    tunes.scorePlaybackSpeed(speed);
    tunes.playScore(score);
  }
}
