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
        objPos foodPos;
        GameMechs* foodGame;

    public:
        Food();
        Food(GameMechs* foodGM);
        ~Food();

        void generateFood(objPosArrayList& blockOff);
        void getFoodPos(objPos &returnPos);

};

#endif