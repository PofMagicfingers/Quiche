#ifndef BeerSprite_h
#define BeerSprite_h

#include <Arduboy2.h>
#include "./BeerState.h"

class BeerSprite // : public Sprite
{
  public:
    BeerSprite(Arduboy2 *arduboy);
    void draw();
    BeerState state = BeerState::FULL;
    int16_t x = 0;
    int16_t y = 0;
    float resize = 1.0;
    uint8_t color = WHITE;
    uint8_t mirror = MIRROR_NONE;

  private:
    Arduboy2 *arduboy;
};

#endif