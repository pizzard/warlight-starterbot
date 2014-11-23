#ifndef SUPERREGION_H_INCLUDED
#define SUPERREGION_H_INCLUDED

//stl
#include <vector>

//project
#include "Region.h"

class SuperRegion
{
public:
	SuperRegion();
	SuperRegion(int pReward);

	virtual ~SuperRegion();
	void addRegion(int noRegion);
	int getNbRegions();

private:
	std::vector<int> regions;
	int nbRegions;
	int reward;
};

#endif // SUPERREGION_H_INCLUDED
