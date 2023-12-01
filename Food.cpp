#include "Food.h"
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"


// defualt constructor
Food::Food()
{
    // foodPos.setObjPos(-1, -1, 'o');

}

Food::Food(GameMechs* foodGM)
{
    foodGame = foodGM;
    foodBucket = new objPosArrayList(); //assigning memory to the foodbucket
}

// destructor
Food::~Food()
{
    delete foodBucket; // deallocating assigned memory
}

void Food::generateFood(objPosArrayList& blockOff, int numFoods)
{
    
    
    srand(time(NULL));

    // Clear the food bucket
    foodBucket->clear();

    int SpecialValue;
    int count = 0; // Variable initialized

    int numSpecialFoods = rand() % 2 + 1;  // Generating 1 or 2 special foods

    for (int i = 0; i < numFoods; ++i) //Looping to spawn all Food elements (5 in this case)
    {
        int candidateX, candidateY;
        int overlap = 1;

        while (overlap) // Continues to try position's if current spawned position overlaps with another board element
        {
            candidateX = rand() % (foodGame->getBoardSizeX() - 2) + 1;
            candidateY = rand() % (foodGame->getBoardSizeY() - 2) + 1; //Generating random food positions on board

            overlap = false;

            for (int j = 0; j < blockOff.getSize(); j++) //Checking all player positions
            {
                objPos tempPos;
                blockOff.getElement(tempPos, j); // Getting player position

                if (candidateX == tempPos.x && candidateY == tempPos.y) //Checking if location overlaps with a player position
                {
                    overlap = true; // If true restart
                    break;
                }
            }

            for (int j = 0; j < foodBucket->getSize(); j++) //Checking all foods
            {
                objPos tempPos;
                foodBucket->getElement(tempPos, j); //Getting food position

                if (candidateX == tempPos.x && candidateY == tempPos.y) //Checking if location overlaps with another food item
                {
                    overlap = true; // If true restart
                    break;
                }
            }
        }

        objPos newFood; 
        newFood.x = candidateX;
        newFood.y = candidateY;
        newFood.symbol = 'w'; //If no overlap assign food to that location with base food type 'w'
        
          

        foodBucket->insertHead(newFood); //Then insert this food into newFood

        count++; //incrementing the count of base type foods spawned

        if (count > numFoods - numSpecialFoods) // BONUS: Checking the amount of base character's is greater than 4 or 3 (depends on numSpecialFoods)
        {
            SpecialValue = rand () % 2; // Randomizing SpecialValue's value to either 0 or 1, result will determine what random food is spawned

             if (SpecialValue) // Checking if SpecialValue is 1
                {
                    objPos newFood;
                    newFood.x = candidateX;
                    newFood.y = candidateY;

                    newFood.symbol = 'l'; //Assign food position and character symbol to 'l'

                    newFood.isSpecial1 = true; // Assigning this character to true for printing logic

                    foodBucket->insertHead(newFood); //Then insert this as the element in newFood
                    
                }
        
            else    //If SpecialValue is 0
            {
                objPos newFood;
                newFood.x = candidateX;
                newFood.y = candidateY;

                newFood.symbol = 'q'; //Assign food position and character symbol to 'q'

                newFood.isSpecial2 = true; // Assigning this character to true for printing logic

                foodBucket->insertHead(newFood); //Then insert this as the element in newFood
            }

        }   
    }
        
}

void Food::getFoodPos(objPos& returnPos)
{
    foodBucket->getHeadElement(returnPos);
}

bool Food::checkFoodCollision(objPos& headPos)
{
    for (int i = 0; i < foodBucket->getSize(); i++) //Looping through food elements
    {
        objPos newFood;
        foodBucket->getElement(newFood, i); //Getting position of food element

        if (headPos.x == newFood.x && headPos.y == newFood.y) //Checking if player and food overlap
        {
            return true; //If there is a collision return true
        }
    }
    return false; //No collision return false
}

objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;
}

int Food ::CheckSpecialFoodCollision(objPos& headPos)
{
    for (int i = 0; i < foodBucket->getSize(); i++) 
    {
        objPos newFood;
        foodBucket->getElement(newFood, i);
        if (headPos.x == newFood.x && headPos.y == newFood.y) // BONUS: Same collision logic as checkFoodCollision
        {
            if (newFood.symbol == 'q') 
            {
                return 1;  //Returning 1 if special character 'q' is found
            } 
            else if (newFood.symbol == 'l')
            {
                return 2; //Returning 2 if special character 'l' is found
            }
        }
    }
    return 0; //Returning 0 if no Special Character Collision
}
