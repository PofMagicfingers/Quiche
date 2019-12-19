#include "GoalSprite.h"

GoalSprite::GoalSprite(Arduboy2 *arduboy) : arduboy(arduboy)
{
}

GoalSprite::~GoalSprite() {
    delete arduboy;
}

void GoalSprite::draw()
{
    arduboy->drawBitmap(position.x, position.y, goal_sprite, 72, 47);
}