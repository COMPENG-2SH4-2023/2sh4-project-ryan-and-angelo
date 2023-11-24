#include "Food.h"
#include "GameMechs.h"
#include "objPos.h"


// defualt constructor
Food::Food()
{
    foodPos.setObjPos(-1, -1, 'o');

}

Food::Food(GameMechs* foodGM)
{
    foodGame = foodGM;
}

// destructor
Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    
    srand(time(NULL));

    int candidateX, candidateY;
    int overlap = 1;  


    while (overlap)
    {
        candidateX = rand() % (foodGame->getBoardSizeX() - 2) + 1;
        candidateY = rand() % (foodGame->getBoardSizeY() - 2) + 1;
        
       
        overlap = (candidateX == blockOff.x && candidateY == blockOff.y);
    }

    foodPos.x = candidateX;
    foodPos.y = candidateY;
    foodPos.symbol = 'o';

}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
