#include "Region.h"
#include <stdio.h>
#include <iostream>
#include "SuperRegion.h"
using namespace std;
Region::Region()
{
    //ctor
}

Region::Region(int pId, int pSuperRegion)
{
    this->superRegion = pSuperRegion;
    id = pId;
}

Region::~Region()
{
    //dtor
}
void Region::addNeighbors(int Neighbors)
{
    neighbors.push_back(Neighbors);
}

void Region::setArmies(int nbArmies)
{
    armies =nbArmies;
}
void Region::setOwner(string pOwner)
{
    owner = pOwner;
}
int Region::getArmies()
{
    return armies;
}
string Region::getOwner()
{
    return owner;
}

int Region::getSuperRegion()
{
    return superRegion;
}

vector<int>& Region::getNeighbors()
{
    return neighbors;
}

