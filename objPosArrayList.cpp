#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //Allocating memory for the array
    listSize=0;
    arrayCapacity = ARRAY_MAX_CAP; //Initialization
}

objPosArrayList::~objPosArrayList()
{
    delete [] aList; //Deallocating memory of the array
}

int objPosArrayList::getSize()
{
    return listSize; //Returning listSize
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize==arrayCapacity)//Checking if listSize is at the max possible length
    {
        return;//Do nothing
    }

    for (int i=listSize; i > 0 ; i--) //Looping through the list
    {
        aList[i].setObjPos(aList[i-1]); //Shuffling elements away from the head
    }

    aList[0].setObjPos(thisPos); //Inserting head at now "vacant" position

    listSize++; //Increasing size
}

void objPosArrayList::insertTail(objPos thisPos)
{

    if (listSize==arrayCapacity) //Checking if listSize is at the max possible length
    {
        return; //Do nothing
    }
    aList[listSize].setObjPos(thisPos); //Otherwise inserting the tail

    listSize++; //Increasing listSize to accomodate for growth
}

void objPosArrayList::removeHead()
{
    if (listSize<=1) //Checking if list is 1 or 0
    { 
        listSize=0; //Set list size to 0 (can't be smaller, no point in removing a 1 element head)
        return;
    }

    for (int i=0; i < listSize-1 ; i++)//Loop through list
    {
        aList[i].setObjPos(aList[i+1]);// Shuffle all list elements away from head
    }

    listSize--; //Shrink listSize to accomodate for change in size
}

void objPosArrayList::removeTail()
{

    if (listSize==0) //Check if listSize is 0
    {
        return; //Do nothing
    }
    listSize--; //Shrink listSize

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]); //Getting Head element
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    if (listSize==0) //Checking if listSize is 0
    {
        return; //Do nothing
    }
    returnPos.setObjPos(aList[listSize-1]); //Gettng tail element
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{

    if (index < 0 || index >= listSize) //Checking for invalid index
    {
        return; //If so do nothing
    }
    aList[index].getObjPos(returnPos); //Otherwise return element
    
}

void objPosArrayList::clear() 
{
    listSize = 0; //Clearing all elements
}