#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Player* playerPtr; 

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
    myPlayer = new Player(myGM);


    
    // playerPtr = new Player(/* Pass your game mechanics reference here */);
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);


    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d , %d> + %c\n", myGM->getBoardSizeX(), myGM->getBoardSizeY(), tempPos.x, tempPos.y, tempPos.symbol);

    //const int BOARD_WIDTH = 20;
    //const int BOARD_HEIGHT = 10;

/*
    objPos player(5, 5, 'P');
    objPos char1(2, 3, 'A');
    objPos char2(7, 4, 'B');
    objPos char3(12, 7, 'C');


    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1) {
                std::cout << "#";
            }
             else if (i == player.y && j == player.x) {
                std::cout << player.getSymbol();
            }
           
            else if ((i == char1.y && j == char1.x) || (i == char2.y && j == char2.x) || (i == char3.y && j == char3.x)) {
                if (i == char1.y && j == char1.x) {
                    std::cout << char1.getSymbol();
                } else if (i == char2.y && j == char2.x) {
                    std::cout << char2.getSymbol();
                } else if (i == char3.y && j == char3.x) {
                    std::cout << char3.getSymbol();
                }
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
`*/


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    // delete playerPtr;
    // playerPtr = nullptr;
    MacUILib_uninit();
}
