#ifndef SUPERREGION_H_INCLUDED
#define SUPERREGION_H_INCLUDED
#include <vector>
#include "Region.h"
using namespace std;
class SuperRegion
{

    std::vector<int> regions;
    int nbRegions;
    int reward;
    public:
        SuperRegion();
        SuperRegion(int pReward);
        virtual ~SuperRegion();
        void addRegion(int noRegion);
        int getNbRegions();
    protected:
    private:
};



#endif // SUPERREGION_H_INCLUDED
