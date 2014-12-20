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
	void setArmies(const int& nbArmies) { armies = nbArmies; }
	void setOwner(const std::string& pOwner){ owner = pOwner; }

	inline int getArmies() { return armies; }
	inline std::string getOwner() { return owner; }
	inline int getSuperRegion() { return superRegion; }
	int getNeighbor(const size_t& index);
    int getNbNeighbors();

private:
	std::vector<int> neighbors;
    int id;
	int superRegion;
	std::string owner;
	int armies;
};

#endif // REGION_H
