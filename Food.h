#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "GameMechs.h"
#include "objPosArrayList.h"



class Food
{
    private:
        GameMechs* foodGame;
        objPosArrayList* foodBucket;

    public:
        Food();
        Food(GameMechs* foodGM);
        ~Food();

        void generateFood(objPosArrayList& blockOff, int numFoods);
        void getFoodPos(objPos& returnPos);
        bool checkFoodCollision(objPos& headPos);
        int CheckSpecialFoodCollision(objPos& headPos);
        objPosArrayList* getFoodBucket();

};

#endif