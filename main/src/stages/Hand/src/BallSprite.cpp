#include "BallSprite.h"

BallSprite::BallSprite(Arduboy2 *arduboy) : arduboy(arduboy)
{
    reset();
}

BallSprite::~BallSprite() {
    delete arduboy;
}

void BallSprite::reset() {
    size = 11;
}

void BallSprite::draw()
{
    switch(size) {
        case 11:
            arduboy->fillCircle(position.x + 30, position.y + 30, 30, BLACK);
            arduboy->drawBitmap(position.x, position.y, ball_sprite_11, 60, 60);
            break;
        case 10:
            arduboy->fillCircle(position.x + 5 + 25, position.y + 5 + 25, 25, BLACK);
            arduboy->drawBitmap(position.x + 5, position.y + 5, ball_sprite_10, 50, 50);
            break;
        case 9:
            arduboy->fillCircle(position.x + 10 + 20, position.y + 10 + 20, 20, BLACK);
            arduboy->drawBitmap(position.x + 10, position.y + 10, ball_sprite_09, 40, 41);
            break;
        case 8:
            arduboy->fillCircle(position.x + 11 + 19, position.y + 11 + 19, 19, BLACK);
            arduboy->drawBitmap(position.x + 11, position.y + 11, ball_sprite_08, 37, 38);
            break;
        case 7:
            arduboy->fillCircle(position.x + 14 + 16, position.y + 14 + 16, 16, BLACK);
            arduboy->drawBitmap(position.x + 14, position.y + 14, ball_sprite_07, 32, 31);
            break;
        case 6:
            arduboy->fillCircle(position.x + 18 + 12, position.y + 18 + 12, 12, BLACK);
            arduboy->drawBitmap(position.x + 18, position.y + 18, ball_sprite_06, 25, 25);
            break;
        case 5:
            arduboy->fillCircle(position.x + 19 + 10, position.y + 19 + 10, 11, BLACK);
            arduboy->drawBitmap(position.x + 19, position.y + 19, ball_sprite_05, 21, 21);
            break;
        case 4:
            arduboy->fillCircle(position.x + 21 + 8, position.y + 21 + 8, 9, BLACK);
            arduboy->drawBitmap(position.x + 21, position.y + 21, ball_sprite_04, 17, 17);
            break;
        case 3:
            arduboy->fillCircle(position.x + 23 + 6, position.y + 23 + 6, 7, BLACK);
            arduboy->drawBitmap(position.x + 23, position.y + 23, ball_sprite_03, 13, 13);
            break;
        case 2:
            arduboy->fillCircle(position.x + 25 + 5, position.y + 25 + 5, 5, BLACK);
            arduboy->drawBitmap(position.x + 25, position.y + 25, ball_sprite_02, 10, 10);
            break;
        case 1:
            arduboy->fillCircle(position.x + 27 + 3, position.y + 27 + 3, 4, BLACK);
            arduboy->drawBitmap(position.x + 27, position.y + 27, ball_sprite_01, 7, 7);
            break;
    }
}