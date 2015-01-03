// stl
#include <iostream>
#include <string>

//project
#include "Bot.h"

Bot::Bot()
	: armiesLeft(0)
	, parser(this)
	, phase(NONE)
{
}

Bot::~Bot()
{

}

void Bot::playGame()
{
	parser.parseInput();
}

void Bot::makeMoves()
{
    /// Output No moves when you have no time left or do not want to commit any moves.
    // std::cout << "No moves\n";
    /// Anatomy of a single move
    //  std::cout << botName << " attack/transfer " << from << " " << to << " "<< armiesMoved;
    /// When outputting multiple moves they must be seperated by a comma
    std::vector<std::string> moves;
    for(size_t j = 0; j < ownedRegions.size(); ++j)
    {
        std::stringstream move;
        int i = ownedRegions[j];
        if(regions[i].getArmies() > 1)
        {
            move << botName << " attack/transfer " << i << " " << regions[i].getNeighbor(std::rand() % regions[i].getNbNeighbors()) << " "<< (regions[i].getArmies()-1);
        }
        moves.push_back(move.str());
    }

    // TODO: use boost::join here as soon the server allows it
    std::stringstream finalMoves;
    for(size_t i = 0; i < moves.size(); ++i)
    {
        finalMoves << moves[i];
        if(i + 1 == moves.size())
        {
            finalMoves << std::endl;
        }
        else
        {
            finalMoves << ",";
        }
    }
    std::cout << finalMoves.str();
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

void Bot::opponentPlacement(const unsigned & noRegion, const int & nbArmies)
{
	// suppress unused variable warnings
	(void)noRegion;
	(void)nbArmies;

    // TODO: STUB
}
void Bot::opponentMovement(const unsigned &noRegion, const unsigned &toRegion, const int &nbArmies)
{
	// suppress unused variable warnings
	(void)noRegion;
	(void)toRegion;
	(void)nbArmies;

    // TODO: STUB
}

void Bot::startDelay(const int& delay)
{
	// suppress unused variable warnings
	(void)delay;
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
    if (phase == Bot::PICK_PREFERRED_REGION)
	{
        std::cout << startingRegionsreceived.front() << "\n";
	}
	if (phase == Bot::PLACE_ARMIES)
	{
        std::cout << botName << " place_armies " << ownedRegions[std::rand() % ownedRegions.size()] << " " << armiesLeft << "\n";
        addArmies(ownedRegions[0], armiesLeft);
	}
	if (phase == Bot::ATTACK_TRANSFER )
	{
        makeMoves();
	}
	phase = NONE;
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
        if(regions[toRegion].getArmies() - std::round(nbArmies*0.6) <= 0)
        {
            regions[toRegion].setArmies(nbArmies - std::round(regions[toRegion].getArmies()*0.7));
            regions[toRegion].setOwner(regions[noRegion].getOwner());
        } else
        {
            regions[noRegion].setArmies(regions[noRegion].getArmies() + nbArmies - std::round(regions[toRegion].getArmies()*0.7));
            regions[toRegion].setArmies(regions[toRegion].getArmies() - std::round(nbArmies*0.6));
        }
	}
}

void Bot::resetRegionsOwned()
{
	ownedRegions.clear();
}
