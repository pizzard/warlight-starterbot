//stl
#include <stdio.h>
#include <iostream>
//project
#include "Region.h"
#include "SuperRegion.h"

Region::Region()
	: id(0)
	, nbNeighbors(0)
	, superRegion(0)
	, armies(0)
{
}

Region::Region(const int& pId, const int& pSuperRegion)
	: id(pId)
	, nbNeighbors(0)
	, superRegion(pSuperRegion)
	, armies(0)
{
}

Region::~Region()
{
}

void Region::addNeighbor(const int& neighbor)
{
	neighbors.push_back(neighbor);
}

void Region::setArmies(const int& nbArmies)
{
	armies = nbArmies;
}
void Region::setOwner(const std::string& pOwner)
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

const std::vector<int>& Region::getNeighbors()
{
	return neighbors;
}

