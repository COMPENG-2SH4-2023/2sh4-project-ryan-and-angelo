#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
// #include "Player.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

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

    while(exitFlag == false)  
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

    exitFlag = false;

    
    // playerPtr = new Player(/* Pass your game mechanics reference here */);
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();



    const int BOARD_WIDTH = 20;
    const int BOARD_HEIGHT = 10;

    objPos topRow, bottomRow, leftColumn, rightColumn;
    topRow.setObjPos(0, 0, '#');
    bottomRow.setObjPos(0, BOARD_HEIGHT - 1, '#');
    leftColumn.setObjPos(0, 0, '#');
    rightColumn.setObjPos(BOARD_WIDTH - 1, 0, '#');

    objPos player(5, 5, 'P'); // Player positioned at (5, 5)

    objPos char1(2, 3, 'A');
    objPos char2(7, 4, 'B');
    objPos char3(12, 7, 'C');

    std::cout << "Initial board:" << std::endl;
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        std::cout << topRow.getSymbol();
    }
    std::cout << std::endl;

    for (int i = 1; i < BOARD_HEIGHT - 1; ++i) {
        std::cout << leftColumn.getSymbol();

        for (int j = 1; j < BOARD_WIDTH - 1; ++j) {

            if (i == player.y && j == player.x) {
                std::cout << player.getSymbol();

            } else if ((i == char1.y && j == char1.x) || (i == char2.y && j == char2.x) || (i == char3.y && j == char3.x)) {

                if (i == char1.y && j == char1.x) {
                    std::cout << char1.getSymbol();

                } 
                else if (i == char2.y && j == char2.x) {
                    std::cout << char2.getSymbol();

                } 
                else if (i == char3.y && j == char3.x) {
                    std::cout << char3.getSymbol();
                }

            } 
            else {
                std::cout << ' ';
            }
        }
        std::cout << rightColumn.getSymbol() << std::endl;
    }

    for (int i = 0; i < BOARD_WIDTH; ++i) {
        std::cout << bottomRow.getSymbol();
    }
    std::cout << std::endl;

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
