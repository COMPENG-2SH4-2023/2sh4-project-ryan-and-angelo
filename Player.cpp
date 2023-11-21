#include "Player.h"
#include "GameMechs.h"




Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos (playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    // not macuilib char
    // get input from where?
    // game mech will find out where to get input
    // it lies within the Gamemechanism* member

    char input = mainGameMechsRef->getInput();

    switch (input)
    {
        case 'w':
            if (myDir != UP && myDir != DOWN)
                myDir = UP;
            break;

        case 'a':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = LEFT;
            break;

        case 's':
            if (myDir != UP && myDir != DOWN)
                myDir = DOWN;
            break;

        case 'd':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT;
            break;

        default:
            break;
        



    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic


if (myDir == UP)
    {
        if (playerPos.y > 0) 
        {
            playerPos.y--;
        }

        if (playerPos.y==0)
        {
            playerPos.y= 13;
        }
    }
    else if (myDir == DOWN)
    {
        if (playerPos.y < 14) 
        {
            playerPos.y++;
        }
        if (playerPos.y == 14)
        {
            playerPos.y=1;
        }
    }
    else if (myDir == LEFT)
    {

        if (playerPos.x > 0) 
        {
            playerPos.x--;
        }
        if (playerPos.x==0)
        {
            playerPos.x=28;
        }
    }
    else if (myDir == RIGHT)
    {

        if (playerPos.x < 29)
        {
            playerPos.x++;
        }
        if (playerPos.x== 29)
        {
            playerPos.x=1;
        }
    }

}

