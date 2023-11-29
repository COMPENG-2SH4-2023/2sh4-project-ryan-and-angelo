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
    foodBucket = new objPosArrayList();
}

// destructor
Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList& blockOff, int numFoods)
{
    
    
    srand(time(NULL));

    // Clear the food bucket
    foodBucket->clear();
    int count =0;
    int Special1;

    int numSpecialFoods = rand() % 2 + 1;  // Generate 1 or 2 special foods
    for (int i = 0; i < numFoods; ++i) {
        int candidateX, candidateY;
        int overlap = 1;

        while (overlap) {
            candidateX = rand() % (foodGame->getBoardSizeX() - 2) + 1;
            candidateY = rand() % (foodGame->getBoardSizeY() - 2) + 1;

            overlap = false;

            for (int j = 0; j < blockOff.getSize(); j++) {
                objPos tempPos;
                blockOff.getElement(tempPos, j);
                if (candidateX == tempPos.x && candidateY == tempPos.y) {
                    overlap = true;
                    break;
                }
            }

            // Check for overlap with the Food Bucket
            for (int j = 0; j < foodBucket->getSize(); j++) {
                objPos tempPos;
                foodBucket->getElement(tempPos, j);
                if (candidateX == tempPos.x && candidateY == tempPos.y) {
                    overlap = true;
                    break;
                }
            }
        }

        objPos newFood;
        newFood.x = candidateX;
        newFood.y = candidateY;
        newFood.symbol = 'w';
        
          

        foodBucket->insertHead(newFood);
        count++;
        if (count >= numFoods - numSpecialFoods)
        {
            Special1 = rand () % 2;
             if (Special1)
                {
                    objPos newFood;
                    newFood.x = candidateX;
                    newFood.y = candidateY;
                    newFood.symbol = 'l';
                    newFood.isSpecial1 = true;
                    foodBucket->insertHead(newFood);
                    
                }
        
            else    
            {
                objPos newFood;
                newFood.x = candidateX;
                newFood.y = candidateY;
                newFood.symbol = 'q';
                newFood.isSpecial2 = true;
                foodBucket->insertHead(newFood);
            }

        }   
    }
        
}

void Food::getFoodPos(objPos& returnPos)
{
    // returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
    foodBucket->getHeadElement(returnPos);
}

void Food::noIncreaseFood()
{   
    int i=0;
    while (i < 9)
    {
        foodGame->incrementScore();
        i++;
    }
}

void Food::pointsLongSnake()
{
    int i=0,j=0;
    while (i < 4)
    {
        foodGame->incrementScore();
        i++;
    }
    
 }

 bool Food::checkFoodCollision(objPos& headPos)
 {
    for (int i = 0; i < foodBucket->getSize(); i++) {
        objPos newFood;
        foodBucket->getElement(newFood, i);
        if (headPos.x == newFood.x && headPos.y == newFood.y) 
        {
            if (newFood.isSpecial2 == true) 
            {
                noIncreaseFood();
                return true;  
            } 
            else if (newFood.isSpecial1 == true)
            {
                pointsLongSnake();
                return true;
            }
            else 
            {
                return true;  
            }
        }
    }
    return false;
 }

objPosArrayList* Food::getFoodBucket()
{
    return foodBucket;
}