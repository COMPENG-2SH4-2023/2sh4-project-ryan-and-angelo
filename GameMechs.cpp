#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?
GameMechs::~GameMechs()
{

}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = 1;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1;
}
