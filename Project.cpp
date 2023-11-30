#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* foodGen;
objPosArrayList* playerPosList;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Player* playerPtr; 
//objPos playerPos(15, 7, 'P');

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 15); // make the board size 26x13
    foodGen = new Food(myGM);
    myPlayer = new Player(myGM, foodGen);
    playerPosList = new objPosArrayList();

    foodGen->generateFood(*playerPosList, 5);
    
    // playerPtr = new Player(/* Pass your game mechanics reference here */);
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    myPlayer->movePlayer();

    myGM->clearInput();

    // if (myPlayer->checkSelfCollision()) 
    // {
    //     myGM->setLoseFlag();
    //     myGM->setExitTrue();
    // } 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPosArrayList* foodBucket = foodGen->getFoodBucket();
    objPos tempFood;

    // Draw player body
    for (int i = 0; i < myGM->getBoardSizeY(); i++) {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) {
            drawn = false;
            for (int k = 0; k < playerBody->getSize(); k++) {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i) {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            // Draw food
            if (!drawn) {
                for (int k = 0; k < foodBucket->getSize(); k++) {
                    foodBucket->getElement(tempFood, k);
                    if (tempFood.x == j && tempFood.y == i) {
                        if (tempFood.isSpecial1) 
                        {
                            MacUILib_printf("%c", tempFood.symbol);  // Change this to the symbol for special food 1
                        } 
                        else if (tempFood.isSpecial2) 
                        {
                            MacUILib_printf("%c", tempFood.symbol);  // Change this to the symbol for special food 2
                        } 
                        else 
                        {
                            MacUILib_printf("%c", tempFood.symbol);
                        }
                        drawn = true;
                        break;
                    }
                }
            }

            // Draw borders
            if (!drawn) {
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) {
                    MacUILib_printf("#");
                } else {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGM->getScore());
    if (myGM->getExitFlagStatus()) {
        MacUILib_printf("End Game\n");
    }
    if (myGM->getExitFlagStatus() && myGM->getLoseFlagStatus()) {
        MacUILib_printf("You Lose!");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
    delete foodGen;
    delete playerPosList;
    delete myGM;
    delete myPlayer;
    MacUILib_uninit();
}
