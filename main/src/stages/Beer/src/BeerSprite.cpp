#include "BeerSprite.h"

BeerSprite::BeerSprite(Arduboy2 *arduboy) : arduboy(arduboy)
{
    reset();
}

BeerSprite::~BeerSprite() {
    delete arduboy;
}

void BeerSprite::reset() {
    beerSeed = random(0, 100) % 2;
    state = BeerState::FULL;
}

void BeerSprite::draw()
{
    switch (state)
    {
    case BeerState::FULL:
        arduboy->drawBitmap(x, y, BEER_FULL, 30, 30);
        break;
    case BeerState::TOP:
        arduboy->drawBitmap(x, y, beerSeed ? BEER_TOP : BEER_TOPTOP, 30, 30);
        break;
    case BeerState::HALF:
        arduboy->drawBitmap(x, y, BEER_HALF, 30, 30);
        break;
    case BeerState::BOTTOM:
        arduboy->drawBitmap(x, y, beerSeed ? BEER_BOTTOM : BEER_BOTTOMBOTTOM, 30, 30);
        break;
    case BeerState::EMPTY:
    case BeerState::RESET:
        arduboy->drawBitmap(x, y, BEER_EMPTY, 30, 30);
        break;
    }
}