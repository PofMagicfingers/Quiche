#ifndef BeerSprite_h
#define BeerSprite_h

#include <Arduboy2.h>
#include "./BeerState.h"

class BeerSprite // : public Sprite
{
  public:
    BeerSprite(Arduboy2 *arduboy);
    ~BeerSprite();
    void draw();
    void reset();
    BeerState state = BeerState::FULL;
    int16_t x = 0;
    int16_t y = 0;
    float resize = 1.0;
    uint8_t color = WHITE;
    uint8_t mirror = MIRROR_NONE;

  private:
    Arduboy2 *arduboy;
    int beerSeed;
};

const unsigned char PROGMEM BEER_FULL[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x02, 0x02, 0x02, 0x02, 0x02, 0x1e, 0x10, 0x0e, 0x02, 0x5e, 0x58, 0x06, 0x02, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_TOPTOP[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1c, 0x10, 0x0c, 0x04, 0x3c, 0x38, 0x0c, 0x04, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_TOP[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x22, 0x22, 0x22, 0x62, 0x42, 0x22, 0x12, 0x22, 0x22, 0xe2, 0xe2, 0x22, 0x22, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_HALF[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x40, 0x40, 0x40, 0x40, 0x40, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x81, 0x01, 0x01, 0x03, 0x02, 0x01, 0x02, 0x01, 0x01, 0x03, 0x03, 0x01, 0x81, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_BOTTOM[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x8c, 0x0c, 0x0c, 0x0a, 0x0a, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x08, 0x0c, 0x8c, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_BOTTOMBOTTOM[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xa0, 0x20, 0x20, 0x20, 0x20, 0x30, 0x30, 0x20, 0x20, 0x40, 0x20, 0x20, 0xa0, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const unsigned char PROGMEM BEER_EMPTY[] = {
0x00, 0x00, 0x00, 0xf8, 0x08, 0xe4, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe4, 0x08, 0xf0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x02, 0x02, 0x0e, 0xf0, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xff, 0x00, 0xff, 0xa0, 0xa0, 0x90, 0x9f, 0x40, 0x3f, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0x0c, 0x09, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x09, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

#endif