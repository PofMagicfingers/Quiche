#include "Game.h"

const char GAMEOVER_STR[] = "GAME OVER";
const char LEVELSDONE_STR[] = " niveaux finis"; 
const char LEVELDONE_STR[] = " niveau fini";

Game::Game()
{
    arduboy = new Arduboy2();
    boomBox = new BoomBox();
}

Game::~Game()
{
    delete arduboy;
    if (currentStage != NULL)
    {
        delete currentStage;
    }
}

void Game::setup()
{
    currentScore.stageDone = 0;
    currentScore.ballsStopped = 0;
    currentScore.beersDrunk = 0;

    arduboy->boot();

    arduboy->blank();
    arduboy->flashlight();
    arduboy->systemButtons();
    arduboy->audio.begin();

    arduboy->setFrameRate(50);
    arduboy->setTextSize(1);

    boomBox->setup(arduboy);
}

void Game::loop()
{
    switch (game_status)
    {
    case GameStatus::MENU:
        menu();
        break;
    case GameStatus::GAMEOVER:
        gameover();
        break;
    case GameStatus::PLAYING:
        playing();
        break;
    }
}

void Game::menu()
{
    if (!arduboy->nextFrame())
        return;

    arduboy->pollButtons();

    arduboy->setTextSize(3);
    arduboy->setCursor(12, quichy);
    arduboy->println("QUICHE");
    arduboy->setTextSize(1);

    if (quichy < 15)
    {
        if (quichy == -50)
        {
            arduboy->digitalWriteRGB(RED_LED, RGB_ON);
        }

        if (quichy == -30)
        {
            arduboy->digitalWriteRGB(RED_LED, RGB_OFF);  // red LED off
            arduboy->digitalWriteRGB(GREEN_LED, RGB_ON); // green LED on
        }

        if (quichy == -10)
        {
            arduboy->digitalWriteRGB(GREEN_LED, RGB_OFF); // green LED off
            arduboy->digitalWriteRGB(BLUE_LED, RGB_ON);   // blue LED on
        }

        if (quichy == 10)
        {
            arduboy->digitalWriteRGB(BLUE_LED, RGB_OFF);
        }

        if (arduboy->everyXFrames(3))
        {
            quichy++;
        }
    }
    else if (quichy == 16)
    {
        quichy++;
    }
    else
    {
        if (!playedBootSound)
        {
            boomBox->tunes->tone(1046, 100);
            arduboy->delayShort(90);
            boomBox->tunes->tone(2093, 500);

            playedBootSound = true;
        }

        if (arduboy->everyXFrames(arduboy->getFrameRate() / 2))
        {
            showStartText++;
        }
        if (showStartText > 0)
        {
            arduboy->setCursor(12, 50);
            arduboy->println("A/B pour commencer");
            if (showStartText >= 3)
            {
                if (!boomBox->isPlaying())
                    boomBox->playRandom();
                showStartText = 0;
            }
        }
    }

    if (playedBootSound && (arduboy->justReleased(A_BUTTON) || arduboy->justReleased(B_BUTTON)))
    {
        currentScore.stageDone = 0;
        currentScore.ballsStopped = 0;
        currentScore.beersDrunk = 0;
        game_status = GameStatus::PLAYING;
    }

    if (arduboy->pressed(RIGHT_BUTTON))
    {
        arduboy->digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
    }

    arduboy->display(CLEAR_BUFFER);
}

void Game::gameover()
{
    if (!arduboy->nextFrame())
        return;

    arduboy->clear();
    arduboy->setTextSize(2);
    arduboy->setCursor(13, 15);
    arduboy->println(GAMEOVER_STR);
    arduboy->setTextSize(1);

    printScores(currentScore);

    arduboy->display(CLEAR_BUFFER);

    arduboy->pollButtons();
    if (arduboy->justReleased(A_BUTTON) || arduboy->justReleased(B_BUTTON))
    {
        game_status = GameStatus::MENU;
    }
}

void Game::printScores(StageScore score) {
    score.stageDone = 13;
    score.beersDrunk = 5;

    arduboy->setCursor(score.stageDone >= 10 ? 19 : score.stageDone > 1 ? 25 : 31, 35);
    arduboy->print(score.stageDone);
    arduboy->println((score.stageDone > 1) ? LEVELSDONE_STR : LEVELDONE_STR);

    arduboy->setCursor(score.ballsStopped >= 10 ? 36 : score.ballsStopped > 1 ? 42 : 48, 44);
    arduboy->print(score.ballsStopped);
    arduboy->println((score.ballsStopped > 1) ? BALLSSTOPPED_STR : BALLSTOPPED_STR);

    arduboy->setCursor(score.beersDrunk >= 10 ? 36 : score.beersDrunk > 1 ? 42 : 48, 53);
    arduboy->print(score.beersDrunk);
    arduboy->println((score.beersDrunk > 1) ? BEERSDRUNK_STR : BEERDRUNK_STR);
}

void Game::playing()
{
    if (!currentStage)
    {

        StageSpeed stageSpeed = StageSpeed::NORMAL;

        if (currentScore.stageDone > 3)
        {
            stageSpeed = StageSpeed::SPEEDY;
        }

        if (currentScore.stageDone > 7)
        {
            stageSpeed = StageSpeed::FAST;
        }

        if (currentScore.stageDone > 10)
        {
            stageSpeed = StageSpeed::INSANE;
        }

        int randed = random(0, 50);

        if (currentScore.stageDone == 0 || currentScore.stageDone > 1 && randed < 26)
        {
            currentStage = new Hand(
                arduboy,
                stageSpeed,
                boomBox);
        }
        else if (currentScore.stageDone == 1 || currentScore.stageDone > 1 && randed > 25)
        {
            currentStage = new Beer(
                arduboy,
                stageSpeed,
                boomBox);
        }

        currentStage->setup();
    }

    if (currentStage)
    {
        arduboy->clear();
        currentStage->loop();
    }

    if (currentStage->isFinished())
    {
        StageScore stageScore = currentStage->getScore();

        if (stageScore.stageDone == 0)
        {
            game_status = GameStatus::GAMEOVER;
        }
        else
        {
            currentScore.stageDone++;
            currentScore.ballsStopped = currentScore.ballsStopped + stageScore.ballsStopped;
            currentScore.beersDrunk = currentScore.beersDrunk + stageScore.beersDrunk; 
            // saveCurrentIfRecord();
        }
        delete currentStage;
        currentStage = NULL;
    }
}