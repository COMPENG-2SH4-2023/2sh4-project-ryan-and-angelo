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
    temporaryPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@'); // Default Player Position

    playerPosList = new objPosArrayList(); //Allocating memory on the heap for the player positions
    
    playerPosList->insertHead(temporaryPos); // Inserting a player symbol at the default position
    
}


Player::~Player()
{
    // delete any heap members here
    // delete thisGMRef;

    delete playerPosList; //Deallocating the player position after constructor usage with the destructor
}


objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list

    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  


    char input = mainGameMechsRef->getInput(); // Getting player input (w,a,s,d)

    switch (input)
    {
        case ' ':
            mainGameMechsRef->setExitTrue(); // If space is pressed, the game will terminate
            break;

        // case 'r':
        //     foodRef->generateFood(*playerPosList, 5); ORIGINAL LOGIC FOR CHANGING FOOD SPAWN POSITION
        //     break;

        case 'w':

            if (myDir != UP && myDir != DOWN)  // Logic to ensure only movement in 90 degree directions

                myDir = UP; // Setting direction if new direction is 90 degrees from the current direction

            break; // Break to prevent other cases from running

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

        default: // If nothing pressed, no change
            break;
        
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos currHead;
    playerPosList->getHeadElement(currHead); // Retrieving position of the player head

    if (checkSelfCollision()) 
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue(); // If the snake has collided with itself, end the game and print the lose screen
    } 

    else // If no collision keep the snake moving
    {
        if (myDir == UP) // Check current direction
        {
            if (currHead.y > 0) 
            {
                currHead.y--; // If not at the border, keep motion going in current direction (in this case up)
            }

            if (currHead.y==0)
            {
                currHead.y= mainGameMechsRef->getBoardSizeY()-2; // If the snake has reached the border, wraparound to opposite side and keep same motion
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

        if (foodRef->checkFoodCollision(currHead)) //Check if new position has collided with a food element
        {
            int collisionResult = foodRef->CheckSpecialFoodCollision(currHead); // BONUS: Storing the result of CheckSpecialFoodCollision (logic to determine if special character was encountered) in a variable for ease

            if (collisionResult == 1) // If player collides with +10 score food
            {
                playerPosList->insertHead(currHead);
                playerPosList->removeTail(); //Ensuring smooth movement upon collection

                for (int j=0; j<10; j++)
                {   
                    mainGameMechsRef->incrementScore(); //Looping to add 10 points
                }

                foodRef->generateFood(*playerPosList, 5); // Regenerating items after collision
            }

            else if (collisionResult == 2) // If player collides with the snake growth food
            {
                playerPosList->insertHead(currHead); //Adding head character first (allows for smoother in game movement)

                for (int z=0; z<5; z++)
                {   
                    mainGameMechsRef->incrementScore(); //Looping to add 5 points
                }

                objPos currTail;
                playerPosList->getTailElement(currTail); // getting current tail position
 
                for (int h=0 ; h < 9; h++)
                {  
                    playerPosList->insertTail(currTail); //Adding length 9 at the tail of the snake (snake continues to move at head while characters are added at the tail)
                }

                foodRef->generateFood(*playerPosList, 5); // Regenerating food after collision
            }   

            else // If neither of the bonus cases, execute normal food collection
            {
            playerPosList->insertHead(currHead);
            mainGameMechsRef->incrementScore();
            foodRef->generateFood(*playerPosList, 5); //Adding head, incrementing score, then regenerating food characters after collision
            }   
        }
    
        else // If player has not collided with a food
        {
            playerPosList->insertHead(currHead);
            playerPosList->removeTail(); // Insert head and remove tail to keep same snake length and movement logic
        }

    }
}

bool Player::checkSelfCollision()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead); //Getting position of current head element

    
    for (int i = 1; i < playerPosList->getSize(); i++) //Looping through all player positions that aren't the head
    {
        objPos tempPos;
        playerPosList->getElement(tempPos, i); // Getting position's of all player elements (minus the head since we already have it)

        if (currHead.x == tempPos.x && currHead.y == tempPos.y) //Checking if any of the player position's overlap (therefore a collision)
        {
            return true; //True if collision
        }
    }

    return false; //False if no collision
}