#include "circulovertice.h"

circuloVertice::circuloVertice()
{
    this->representavertice=nullptr;
    this->name="";
    this->x=0;
    this->y=0;
}


bool circuloVertice::createVertice(string name,int x, int y)
{
    this->name=name;
    this->x=x;
    this->y=y;
    return true;
}
