#ifndef REGION_H
#define REGION_H

//stl
#include <vector>
#include <string>

class Region
{
public:
	Region();
	Region(const int& pId, const  int& superRegion);

	virtual ~Region();
	void addNeighbor(const int& neighbor);
	void setArmies(const int& nbArmies);
	void setOwner(const std::string& owner);
	int getArmies();
	std::string getOwner();
	int getSuperRegion();
	const std::vector<int>& getNeighbors();

private:
	std::vector<int> neighbors;
	int id;
	int nbNeighbors;
	int superRegion;
	std::string owner;
	int armies;
};

#endif // REGION_H
