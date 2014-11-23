//stl
#include <stdio.h>
#include <iostream>
//project
#include "Region.h"
#include "SuperRegion.h"

Region::Region()
{

}

Region::Region(int pId, int pSuperRegion)
{
	this->superRegion = pSuperRegion;
	id = pId;
}

Region::~Region()
{

}
void Region::addNeighbors(int Neighbors)
{
	neighbors.push_back(Neighbors);
}

void Region::setArmies(int nbArmies)
{
	armies = nbArmies;
}
void Region::setOwner(std::string pOwner)
{
	owner = pOwner;
}
int Region::getArmies()
{
	return armies;
}
std::string Region::getOwner()
{
	return owner;
}

int Region::getSuperRegion()
{
	return superRegion;
}

std::vector<int>& Region::getNeighbors()
{
	return neighbors;
}

