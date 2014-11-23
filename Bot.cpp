// stl
#include <iostream>
#include <string>

//project
#include "Bot.h"

Bot::Bot()
	: armiesLeft(0)
	, parser(this)
{
}

Bot::~Bot()
{

}

void Bot::playGame()
{
	parser.parseInput();
}    //plays a single game of Warlight

void Bot::makeMoves()
{

}   //makes moves for a single turn
void Bot::endTurn()
{

}     //indicates to the engine that it has made its move

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
	regions[noRegion].addNeighbors(neighbors);
	regions[neighbors].addNeighbors(noRegion);
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

void Bot::addStartingRegion(const unsigned& noRegion)
{
	startingRegionsreceived.push_back(noRegion);
}

void Bot::startDelay(const int& /* delay */)
{

}
void Bot::setPhase(const std::string& pPhase)
{
	phase = pPhase;
}
void Bot::executeAction()
{
	if (phase == "")
		return;
	if (phase == "pickPreferredRegion")
	{
		unsigned i, nbAns = 0;
		for (i = 0; i < startingRegionsreceived.size() && nbAns < 6; i++)
		{
			std::cout << startingRegionsreceived[i];
			nbAns++;
			if (nbAns < 6)
				std::cout << " ";
			else
			{
				std::cout << "\n";
				break;
			}
		}
	}
	if (phase == "place_armies")
	{
		std::cout << botName << " place_armies " << ownedRegions[0] << " " << armiesLeft << "\n";
	}
	if (phase == "attack/transfer")
	{
		std::cout << "No moves\n";
//          std::cout << botName << " attack/transfer " << from << " " << to << " "<< armiesMoved;
	}
	phase.clear();
}

void Bot::updateRegion(const unsigned& noRegion, const std::string& playerName, const int& nbArmies)
{
	regions[noRegion].setArmies(nbArmies);
	regions[noRegion].setOwner(playerName);
	if (playerName == botName)
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
	}
}

void Bot::resetRegionsOwned()
{
	ownedRegions.clear();
}
