
#ifndef BOT_H
#define BOT_H
#include <iostream>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <vector>
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"

class Bot
{
    std::ifstream in;
    std::vector<Region> regions;
    std::vector<SuperRegion> superRegions;
    std::string botName;
    std::string opponentBotName;
    std::vector<int> startingRegionsreceived;
    std::vector<int> ownedRegions;
    int armiesLeft;
    Parser parser;
    std::string phase;
    public:
        Bot();
        virtual ~Bot();

    void playGame();    //plays a single game of Warlight

    void makeMoves();   //makes moves for a single turn
    void endTurn();     //indicates to the engine that it has made its moves
    void addRegion(unsigned noRegion, unsigned noSuperRegion);
    void addSuperRegion(unsigned noSuperRegion, int reward);
    void addNeighbors(unsigned noRegion, unsigned Neighbors);
    void setBotName(std::string name);
    void setOpponentBotName(std::string name);
    void setArmiesLeft(int nbArmies);
    void addArmies(unsigned noRegion,int nbArmies);
    void moveArmies(unsigned noRegion,unsigned toRegion,int nbArmies);
    void addStartingRegion(unsigned noRegion);
    void startDelay(int delay);
    void setPhase(std::string pPhase);
    void executeAction();
    void updateRegion(unsigned noRegion, std::string playerName, int nbArmies);
    void resetRegionsOwned();

    private:
};

#endif // BOT_H
