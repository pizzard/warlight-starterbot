//stl
#include <stdio.h>
#include <iostream>
//project
#include "Region.h"
#include "SuperRegion.h"

Region::Region()
	: id(0)
	, superRegion(0)
	, owner(NEUTRAL)
	, armies(0)
{
}

Region::Region(const int& pId, const int& pSuperRegion)
	: id(pId)
	, superRegion(pSuperRegion)
	, owner(NEUTRAL)
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

int Region::getNbNeighbors() const
{
	return neighbors.size();
}

int Region::getNeighbor(const size_t& index) const
{
	return neighbors.at(index);
}

