#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"




Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included

    // playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    objPos temporaryPos;
    temporaryPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(temporaryPos);

    playerPosList->insertHead(temporaryPos);
    playerPosList->insertHead(temporaryPos);
    playerPosList->insertHead(temporaryPos);
    playerPosList->insertHead(temporaryPos);
    

}


Player::~Player()
{
    // delete any heap members here
    // delete thisGMRef;

    delete playerPosList;
}

// void Player::getPlayerPos(objPos &returnPos)

objPosArrayList* Player :: getPlayerPos()
{
    // return the reference to the playerPos arrray list

    // returnPos.setObjPos (playerPos.x, playerPos.y, playerPos.symbol);

    return playerPosList;
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
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;

        case 'r':
            // getPlayerPos(playerPos); 
            // foodRef->generateFood(playerPos);
            break;

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

objPos currHead;
playerPosList->getHeadElement(currHead);



if (myDir == UP)
    {
        if (currHead.y > 0) 
        {
            currHead.y--;
        }

        if (currHead.y==0)
        {
            currHead.y= mainGameMechsRef->getBoardSizeY()-2;
        }
    }
    else if (myDir == DOWN)
    {
        if (currHead.y < mainGameMechsRef->getBoardSizeY()-1) 
        {
            currHead.y++;
        }
        if (currHead.y == mainGameMechsRef->getBoardSizeY()-1)
        {
            currHead.y=1;
        }
    }
    else if (myDir == LEFT)
    {

        if (currHead.x > 0) 
        {
            currHead.x--;
        }
        if (currHead.x==0)
        {
            currHead.x= mainGameMechsRef->getBoardSizeX()-2;
        }
    }
    else if (myDir == RIGHT)
    {

        if (currHead.x < mainGameMechsRef->getBoardSizeX()-1)
        {
            currHead.x++;
        }
        if (currHead.x== mainGameMechsRef->getBoardSizeX()-1)
        {
            currHead.x=1;
        }
    }

playerPosList->insertHead(currHead);
playerPosList->removeTail();
// if (myDir == UP)
//     {
//         if (playerPos.y > 0) 
//         {
//             playerPos.y--;
//         }

//         if (playerPos.y==0)
//         {
//             playerPos.y= mainGameMechsRef->getBoardSizeY()-2;
//         }
//     }
//     else if (myDir == DOWN)
//     {
//         if (playerPos.y < mainGameMechsRef->getBoardSizeY()-1) 
//         {
//             playerPos.y++;
//         }
//         if (playerPos.y == mainGameMechsRef->getBoardSizeY()-1)
//         {
//             playerPos.y=1;
//         }
//     }
//     else if (myDir == LEFT)
//     {

//         if (playerPos.x > 0) 
//         {
//             playerPos.x--;
//         }
//         if (playerPos.x==0)
//         {
//             playerPos.x= mainGameMechsRef->getBoardSizeX()-2;
//         }
//     }
//     else if (myDir == RIGHT)
//     {

//         if (playerPos.x < mainGameMechsRef->getBoardSizeX()-1)
//         {
//             playerPos.x++;
//         }
//         if (playerPos.x== mainGameMechsRef->getBoardSizeX()-1)
//         {
//             playerPos.x=1;
//         }
//     }

}

