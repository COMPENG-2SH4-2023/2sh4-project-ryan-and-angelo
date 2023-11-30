#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"



Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included

    objPos temporaryPos;
    temporaryPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(temporaryPos);
    
}


Player::~Player()
{
    // delete any heap members here
    // delete thisGMRef;

    delete playerPosList;
}


objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list

    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  


    char input = mainGameMechsRef->getInput();

    switch (input)
    {
        case ' ':
            mainGameMechsRef->setExitTrue();
            break;

        case 'r':
            foodRef->generateFood(*playerPosList, 5);
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

    if (checkSelfCollision()) 
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    } 

    else
    {
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

        if (foodRef->checkFoodCollision(currHead))
        {
            int collisionResult = foodRef->getFoodSymbol(currHead);

            if (collisionResult == 1)
            {
                playerPosList->insertHead(currHead);

                playerPosList->removeTail();

                for (int j=0; j<10; j++)
                {   
                    mainGameMechsRef->incrementScore();
                }

                foodRef->generateFood(*playerPosList, 5);
            }

            else if (collisionResult == 2) 
            {
                playerPosList->insertHead(currHead);
                mainGameMechsRef->incrementScore();
                objPos currTail;
                playerPosList->getTailElement(currTail);
 
                for (int h=0; h < 9; h++)
                {   mainGameMechsRef->incrementScore();
                    playerPosList->insertTail(currTail);
                }

                foodRef->generateFood(*playerPosList, 5);
            }   

            else
            {
            playerPosList->insertHead(currHead);

            mainGameMechsRef->incrementScore();
            foodRef->generateFood(*playerPosList, 5);
            }   
        }
    
        else 
        {
            playerPosList->insertHead(currHead);
            playerPosList->removeTail();
        }

    }
}

bool Player::checkSelfCollision()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos tempPos;
        playerPosList->getElement(tempPos, i);

        if (currHead.x == tempPos.x && currHead.y == tempPos.y)
        {
            return true;
        }
    }

    return false;
}