#include "Beer.h"

const String score_label_singular = " biere";
const String score_label = " bieres";

Beer::Beer(Arduboy2 *arduboy, StageSpeed speed, BoomBox *bbox) : Stage(arduboy, speed, bbox)
{
    level_music = Music::CONNEMARA;
    beerSprite = new BeerSprite(_arduboy);
    speedFactor = 1.0/sqrt((double)speed);
    startDuration = 1.0 * speedFactor;
    runningDuration = round(8.0 * speedFactor);
    endDuration = 1.5 * speedFactor;
}

Beer::~Beer() {
    delete beerSprite;
}

void Beer::newBeer()
{
    currentBeerState = BeerState::FULL;
    currentBeerSips = 0;
    beerSprite->reset();
}

void Beer::setup()
{
    Stage::setup();
    newBeer();
    beerSprite->y = 25;
    beerSprite->x = -30;

    goPosition.x = 100;
    goPosition.y = 20;

    setStatus(StageStatus::STARTING);
}

void Beer::drawTimer(double time) {
    _arduboy->setCursor(95, 45);
    _arduboy->print(time);
    _arduboy->println("s");
}

void Beer::startingLoop()
{
    if (beerSprite->x < 30)
    {
        transition(
            (startDuration * 0.75),
            60,
            30,
            1,
            beerSprite->x
        );
    }
    else
    {
        drawTimer(runningDuration);
        _arduboy->setCursor(85, 35);
        _arduboy->print("0 biere");    
    }

    showInstructions();

    beerSprite->draw();
}

void Beer::showInstructions() {
        _arduboy->setCursor(3, 0);
    _arduboy->println("Bois un max de bieres !");
    if(speed != StageSpeed::NORMAL) {
        _arduboy->setCursor(5, 10);
        _arduboy->print("vit. x");
        _arduboy->print((int)speed);
    }
}

void Beer::runningLoop()
{
    if (_arduboy->justReleased(A_BUTTON) || _arduboy->justReleased(B_BUTTON))
        currentBeerSips++;

    BeerState state = (BeerState)currentBeerSips;

    if (state != currentBeerState)
    {
        currentBeerState = state;
        beerSprite->state = state;

        if (state == BeerState::RESET)
        {
            boomBox->tunes->tone(500, 20);
            _arduboy->delayShort(100);
            boomBox->tunes->tone(800, 100);
            newBeer();
            score++;
        }
    }

    showInstructions();

    scorePosition.x = 85 - ((score > 9 ? 2 : score > 1 ? 1 : 0) * 5);
    scorePosition.y = 35;
    _arduboy->setCursor(scorePosition.x, scorePosition.y);

    _arduboy->print(score);
    _arduboy->print((score > 1 ? score_label : score_label_singular));

    drawTimer(stageTimer->timeOutSec - stageTimer->timeElapsed());

    beerSprite->draw();
}

void Beer::endingLoop()
{
    _arduboy->setCursor(0, 0);

    transition(
        (endDuration * 0.75),
        45,
        70,
        -1,
        beerSprite->y
    );

    int scoreDestX = round(
        (
            WIDTH - 5 -
            (
                (score > 10 ? 6.5 : 0) + 
                (score > 1 ? 5 : 6) * 6.5
            )
        ) / 2
    );

    transition(
        (endDuration * 0.75),
        (85-scoreDestX),
        scoreDestX,
        -1,
        scorePosition.x
    );

    transition(
        (endDuration * 0.75),
        5,
        30,
        -1,
        scorePosition.y
    );

    _arduboy->setCursor(scorePosition.x, scorePosition.y);
    _arduboy->print(score);
    _arduboy->print((score > 1 ? score_label : score_label_singular));

    beerSprite->draw();
}

void Beer::wrapUp()
{
    _arduboy->display(CLEAR_BUFFER);
    Stage::wrapUp();
}
