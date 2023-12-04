#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

//Refrences to classes
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


int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  // ExitFlag call
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

    //Allocating memory onto the heap for desired instances of classes for the boardsize, food, player, and player list
    myGM = new GameMechs(30, 15); 
    foodGen = new Food(myGM); 
    myPlayer = new Player(myGM, foodGen); 
    playerPosList = new objPosArrayList(); 

    foodGen->generateFood(*playerPosList, 5); //Generating Foods onto the board
}

void GetInput(void)
{
   myGM->getInput(); //Get player input
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();

    myPlayer->movePlayer();

    myGM->clearInput(); //Running player movement and collision logic dependent on player input, then clearing input for next iteration

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn; //Setting variable drawn to check to see if another item has already been printed at a board location

    objPosArrayList* playerBody = myPlayer->getPlayerPos(); //Getting Player Position
    objPos tempBody; 

    objPosArrayList* foodBucket = foodGen->getFoodBucket(); //Getting Food Position
    objPos tempFood; 

    for (int i = 0; i < myGM->getBoardSizeY(); i++) 
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) //Looping through the bound's of the game board
        {
            drawn = false;

            for (int k = 0; k < playerBody->getSize(); k++) //Checking player position's
            {
                playerBody->getElement(tempBody, k); //Getting player position's

                if (tempBody.x == j && tempBody.y == i) //Checking if current board position aligns with player position
                {
                    MacUILib_printf("%c", tempBody.symbol); //Printing the player position

                    drawn = true; //Something was drawn at this index

                    break; //Go to next check
                }
            }

            // Draw food
            if (!drawn) // Check if another item has  been drawn at this index
            {
                for (int k = 0; k < foodBucket->getSize(); k++) //Loop through food's
                {
                    foodBucket->getElement(tempFood, k); //Get the food position

                    if (tempFood.x == j && tempFood.y == i) //Check if the food position aligns with the current board index
                    {
                        if (tempFood.isSpecial1) // Bonus:Check if food is the first type of special food (score food)
                        {
                            MacUILib_printf("%c", tempFood.symbol);  // Change this to the symbol for special food 1
                        } 

                        else if (tempFood.isSpecial2) //Check if food is the second type of special food (snake growth)
                        {
                            MacUILib_printf("%c", tempFood.symbol);  // Change this to the symbol for special food 2
                        } 

                        else 
                        {
                            MacUILib_printf("%c", tempFood.symbol); //Otherwise print the base food type
                        }

                        drawn = true; //Element has been printed
                        break;
                    }
                }
            }

            // Draw borders
            if (!drawn) 
            {
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) 
                {
                    MacUILib_printf("#"); //If we are at a border value, print #
                } 
                else
                {
                    MacUILib_printf(" "); //If none of the other items have been printed, print a blank space
                }
            }
        }
        MacUILib_printf("\n"); //Print newline for future statements
    }

    MacUILib_printf("Score: %d\n", myGM->getScore()); // Printing current score

    // Game Instructions for different food values
    MacUILib_printf("'o' -> Score: +1, Length: +1\n");
    MacUILib_printf("'*' -> Score: +10, Length: +0\n");
    MacUILib_printf("'+' -> Score: +5, Length: +10\n");

    if(!myGM->getExitFlagStatus())
    {
        MacUILib_printf("\nPress SPACEBAR to End Game"); // End Game Instuctions
    }

    if (myGM->getExitFlagStatus()) 
    {
        MacUILib_printf("\nEnd Game\n"); //Printing End Game if program has been terminated
    }

    if (myGM->getExitFlagStatus() && myGM->getLoseFlagStatus()) 
    {
        MacUILib_printf("You Lose!"); //Printing You Lose! if game is over and player has lost (collided with itself)
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen(); Commented out so that end game screen can still be seen
    delete foodGen;
    delete playerPosList;
    delete myGM;
    delete myPlayer;  // Deallocating memory in all areas that created memory on the heap
    MacUILib_uninit();
}
