#include "QuicheSprite.h"

QuicheSprite::QuicheSprite(Arduboy2 *arduboy) : arduboy(arduboy)
{
    reset();
}

QuicheSprite::~QuicheSprite()
{
    delete arduboy;
}

void QuicheSprite::reset()
{
    direction = Direction::NONE;
}

void QuicheSprite::draw()
{
    switch (direction)
    {
    case Direction::NONE:
        if (arduboy->everyXFrames(arduboy->getFrameRate() / 3))
        {
            idle_position++;
        }
        if (idle_position < 5)
        {
            arduboy->fillCircle(position.x + 21, position.y + 14, 12, BLACK);
            arduboy->drawBitmap(position.x, position.y, quiche_idle_0, 42, 32);
        }
        else if (idle_position < 10)
        {
            arduboy->fillCircle(position.x + 21, position.y + 14, 12, BLACK);
            arduboy->drawBitmap(position.x + 1, position.y, quiche_idle_1, 40, 32);
        }
        else if (idle_position < 15)
        {
            arduboy->fillCircle(position.x + 21, position.y + 14, 12, BLACK);
            arduboy->drawBitmap(position.x, position.y, quiche_idle_0, 42, 32);
        }
        else if (idle_position <= 20)
        {
            arduboy->fillCircle(position.x + 21, position.y + 14, 12, BLACK);
            arduboy->drawBitmap(position.x + 1, position.y, quiche_idle_2, 40, 32);
        }
        if (idle_position >= 20)
        {
            idle_position = 0;
        }
        break;
    case Direction::LEFT:
        arduboy->fillCircle(position.x + 11, position.y + 16, 12, BLACK);
        arduboy->drawBitmap(position.x - 10, position.y + 2, quiche_left, 39, 34);
        break;
    case Direction::RIGHT:
        arduboy->fillCircle(position.x + 28, position.y + 16, 12, BLACK);
        arduboy->drawBitmap(position.x + 10, position.y + 3, quiche_right, 39, 32);
        break;
    case Direction::UP:
        arduboy->fillCircle(position.x + 21, position.y + 6, 12, BLACK);
        arduboy->drawBitmap(position.x + 3, position.y - 8, quiche_up, 34, 33);
        break;
    case Direction::DOWN:
        arduboy->fillCircle(position.x + 21, position.y + 14, 12, BLACK);
        arduboy->drawBitmap(position.x + 3, position.y, quiche_down, 34, 32);
        break;
    }
}