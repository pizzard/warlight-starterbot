#ifndef REGION_H
#define REGION_H
#include <vector>
#include <string>
class Region
{

    std::vector<int> neighbors;
    int id;
    int nbNeighbors;
    int superRegion;
    std::string owner;
    int armies;
    public:
        Region();
        Region(int pId,int superRegion);
        virtual ~Region();
        void addNeighbors(int Neighbors);
        void setArmies(int nbArmies);
        void setOwner(std::string owner);
        int getArmies();
        std:: string getOwner();
        int getSuperRegion();
        std::vector<int>& getNeighbors();
    protected:
    private:
};

#endif // REGION_H
