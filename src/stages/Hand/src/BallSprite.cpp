#include "BallSprite.h"

BallSprite::BallSprite(Arduboy2 *arduboy) : arduboy(arduboy)
{
    reset();
}

BallSprite::~BallSprite() {
    delete arduboy;
}

void BallSprite::reset() {
}

void BallSprite::draw()
{
}