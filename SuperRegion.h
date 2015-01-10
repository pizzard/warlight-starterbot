#ifndef SUPERREGION_H_INCLUDED
#define SUPERREGION_H_INCLUDED

// stl
#include <vector>

// project
#include "main.h"
#include "Region.h"

class SuperRegion
{
public:
	SuperRegion();
	SuperRegion(const int& pReward);

	virtual ~SuperRegion();
	void addRegion(const int& region);
	size_t size() { return regions.size(); }

private:
	std::vector<int> regions;
	int reward;
};

#endif // SUPERREGION_H_INCLUDED
