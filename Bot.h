#ifndef BOT_H
#define BOT_H

// stl
#include <iostream>
#include <fstream>
#include <vector>

// project
#include "Parser.h"
#include "Region.h"
#include "SuperRegion.h"

class Bot
{

public:
	enum Phase {
		NONE,
		PICK_PREFERRED_REGION,
		FIND_BORDERS,
		PLACE_ARMIES,
		ATTACK_TRANSFER
	};

	Bot();
	virtual ~Bot();

	void playGame();    //plays a single game of Warlight

	void makeMoves();   //makes moves for a single turn
	void endTurn();     //indicates to the engine that it has made its moves
	void addRegion(const unsigned& noRegion, const unsigned& noSuperRegion);
	void addSuperRegion(const unsigned& noSuperRegion, const int& reward);
	void addNeighbors(const unsigned& noRegion, const unsigned& Neighbors);
	void setBotName(const std::string& name);
	void setOpponentBotName(const std::string& name);
	void setArmiesLeft(const int& nbArmies);
	void addArmies(const unsigned& noRegion, const int& nbArmies);
	void moveArmies(const unsigned& noRegion, const unsigned& toRegion, const int& nbArmies);
	void addStartingRegion(const unsigned& noRegion);
	void startDelay(const int& delay);

	void setPhase(const Phase phase);

	void executeAction();
	void updateRegion(const unsigned& noRegion, const std::string& playerName, const int& nbArmies);
	void resetRegionsOwned();

private:
	std::ifstream in;
	std::vector<Region> regions;
	std::vector<SuperRegion> superRegions;
	std::string botName;
	std::string opponentBotName;
	std::vector<int> startingRegionsreceived;
	std::vector<int> ownedRegions;
	int armiesLeft;
	Parser parser;
	Phase phase;
};

#endif // BOT_H
