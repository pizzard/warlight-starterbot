// stl
#include <iostream>
#include <string>

//project
#include "Bot.h"

//tools
#include "tools/StringManipulation.h"

Bot::Bot() :
		armiesLeft(0), timebank(0), timePerMove(0), maxRounds(0), parser(this), phase(NONE)
{
}

Bot::~Bot()
{

}

void Bot::playGame()
{
	parser.parseInput();
}

void Bot::pickStartingRegion()
{
	// START HERE!
	std::cout << startingRegionsreceived.front() << std::endl;
}

void Bot::placeArmies()
{
	// START HERE!
	unsigned region = std::rand() % ownedRegions.size();
	std::cout << botName << " place_armies " << ownedRegions[region] << " " << armiesLeft
			<< std::endl;
	addArmies(ownedRegions[region], armiesLeft);
}

void Bot::makeMoves()
{
	// START HERE!
	/// Output No moves when you have no time left or do not want to commit any moves.
	// std::cout << "No moves "  << std::endl;
	/// Anatomy of a single move
	//  std::cout << botName << " attack/transfer " << from << " " << to << " "<< armiesMoved;
	/// When outputting multiple moves they must be seperated by a comma
	std::vector<std::string> moves;
	for (size_t j = 0; j < ownedRegions.size(); ++j)
	{
		std::stringstream move;
		int i = ownedRegions[j];
		if (regions[i].getArmies() <= 1)
			continue;

		int target = regions[i].getNeighbor(std::rand() % regions[i].getNbNeighbors());
		// prefer enemy regions
		for ( unsigned k = 0; k < 5; ++k)
		{
			if(regions[target].getOwner() != ME) break;
			target = regions[i].getNeighbor(std::rand() % regions[i].getNbNeighbors());
		}
		move << botName << " attack/transfer " << i << " "
				<< target << " "
				<< (regions[i].getArmies() - 1);
		moves.push_back(move.str());
	}

	std::cout << string::join(moves) << std::endl;
}

void Bot::addRegion(const unsigned& noRegion, const unsigned& noSuperRegion)
{
	while (regions.size() <= noRegion)
	{
		regions.push_back(Region());
	}
	regions[noRegion] = Region(noRegion, noSuperRegion);
	superRegions[noSuperRegion].addRegion(noRegion);
}
void Bot::addNeighbors(const unsigned& noRegion, const unsigned& neighbors)
{
	regions[noRegion].addNeighbor(neighbors);
	regions[neighbors].addNeighbor(noRegion);
}
void Bot::addWasteland(const unsigned &noRegion)
{
	wastelands.push_back(noRegion);
}
void Bot::addSuperRegion(const unsigned& noSuperRegion, const int&reward)
{
	while (superRegions.size() <= noSuperRegion)
	{
		superRegions.push_back(SuperRegion());
	}
	superRegions[noSuperRegion] = SuperRegion(reward);
}

void Bot::setBotName(const std::string& name)
{
	botName = name;
}
void Bot::setOpponentBotName(const std::string& name)
{
	opponentBotName = name;
}
void Bot::setArmiesLeft(const int& nbArmies)
{
	armiesLeft = nbArmies;
}
void Bot::setTimebank(const int &newTimebank)
{
	timebank = newTimebank;
}
void Bot::setTimePerMove(const int &newTimePerMove)
{
	timePerMove = newTimePerMove;
}
void Bot::setMaxRounds(const int &newMaxRounds)
{
	maxRounds = newMaxRounds;
}

void Bot::clearStartingRegions()
{
	startingRegionsreceived.clear();
}

void Bot::addStartingRegion(const unsigned& noRegion)
{
	startingRegionsreceived.push_back(noRegion);
}

void Bot::addOpponentStartingRegion(const unsigned& noRegion)
{
	opponentStartingRegions.push_back(noRegion);
}
void Bot::opponentPlacement(const unsigned & noRegion, const int & nbArmies)
{
	// suppress unused variable warnings
	(void) noRegion;
	(void) nbArmies;

	// TODO: STUB
}
void Bot::opponentMovement(const unsigned &noRegion, const unsigned &toRegion, const int &nbArmies)
{
	// suppress unused variable warnings
	(void) noRegion;
	(void) toRegion;
	(void) nbArmies;

	// TODO: STUB
}

void Bot::startDelay(const int& delay)
{
	// suppress unused variable warnings
	(void) delay;
	// TODO: STUB
}
void Bot::setPhase(const Bot::Phase pPhase)
{
	phase = pPhase;
}
void Bot::executeAction()
{
	if (phase == NONE)
		return;
	if (phase == Bot::PICK_STARTING_REGION)
	{
		pickStartingRegion();
	}
	else if (phase == Bot::PLACE_ARMIES)
	{
		placeArmies();
	}
	else if (phase == Bot::ATTACK_TRANSFER)
	{
		makeMoves();
	}
	phase = NONE;
}

void Bot::updateRegion(const unsigned& noRegion, const  std::string& playerName, const int& nbArmies)
{
	Player owner;
	if (playerName == botName)
		owner = ME;
	else if (playerName == opponentBotName)
		owner = ENEMY;
	else
		owner = NEUTRAL;
	regions[noRegion].setArmies(nbArmies);
	regions[noRegion].setOwner(owner);
	if (owner == ME)
		ownedRegions.push_back(noRegion);
}
void Bot::addArmies(const unsigned& noRegion, const int& nbArmies)
{
	regions[noRegion].setArmies(regions[noRegion].getArmies() + nbArmies);
}
void Bot::moveArmies(const unsigned& noRegion, const unsigned& toRegion, const int& nbArmies)
{
	if (regions[noRegion].getOwner() == regions[toRegion].getOwner() && regions[noRegion].getArmies() > nbArmies)
	{
		regions[noRegion].setArmies(regions[noRegion].getArmies() - nbArmies);
		regions[toRegion].setArmies(regions[toRegion].getArmies() + nbArmies);
	}
	else if (regions[noRegion].getArmies() > nbArmies)
	{
		regions[noRegion].setArmies(regions[noRegion].getArmies() - nbArmies);
		if (regions[toRegion].getArmies() - std::round(nbArmies * 0.6) <= 0)
		{
			regions[toRegion].setArmies(nbArmies - std::round(regions[toRegion].getArmies() * 0.7));
			regions[toRegion].setOwner(regions[noRegion].getOwner());
		}
		else
		{
			regions[noRegion].setArmies(
					regions[noRegion].getArmies() + nbArmies - std::round(regions[toRegion].getArmies() * 0.7));
			regions[toRegion].setArmies(regions[toRegion].getArmies() - std::round(nbArmies * 0.6));
		}
	}
}

void Bot::resetRegionsOwned()
{
	ownedRegions.clear();
}
