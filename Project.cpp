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
    //MacUILib_clearScreen();

    myGM = new GameMechs(30, 15); // make the board size 26x13
    foodGen = new Food(myGM);
    myPlayer = new Player(myGM, foodGen);

    objPos playerPos {-1,-1,'o'};

    // objPos playerPos;
    // myPlayer->getPlayerPos(playerPos);

    foodGen->generateFood(playerPos);
    
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
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    // objPos tempPos;
    // myPlayer->getPlayerPos(tempPos);

    objPosArrayList* playerBody =myPlayer->getPlayerPos();
    objPos tempBody;

    objPos foodPos;
    foodGen->getFoodPos(foodPos);



      

    for (int i = 0; i < myGM->getBoardSizeY(); i++) {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) {
            drawn = false;
            for (int k =0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x==j && tempBody.y==i)
                {
                    MacUILib_printf("%c",tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            
            if (drawn)
            {
                continue;
            }

            if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) {
                MacUILib_printf("#");
            }
            
            else if (i == foodPos.y && j == foodPos.x) {
                MacUILib_printf("%c", foodPos.symbol);
            }
            else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }



    // MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d , %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);


    // for (int i = 0; i < myGM->getBoardSizeY(); i++) {
    //     for (int j = 0; j < myGM->getBoardSizeX(); j++) {
    //         if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) {
    //             MacUILib_printf("#");
    //         }
    //         else if (i == tempPos.y && j == tempPos.x) {
    //             MacUILib_printf("%c", tempPos.getSymbol());
    //         }
    //         else if (i == foodPos.y && j == foodPos.x) {
    //             MacUILib_printf("%c", foodPos.symbol);
    //         }
    //         else {
    //             MacUILib_printf(" ");
    //         }
    //     }
    //     MacUILib_printf("\n");
    // }



}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
    delete foodGen;

    delete myGM;
    delete myPlayer;
    MacUILib_uninit();
}
