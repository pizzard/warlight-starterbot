//stl
#include <iostream>
#include <stdlib.h>

// project
#include "Bot.h"
#include "Parser.h"

Parser::Parser(Bot* bot)
	:theBot(bot)
{
}

Parser::~Parser()
{
}

void Parser::parseInput()
{
	std::string inputType;
	while (std::cin >> inputType)
	{
		if (inputType == "setup_map")
			parseSetup_Map();
		else if (inputType == "pick_starting_regions")
			parseStarting_Regions();
		else if (inputType == "settings")
			parseSettings();
		else if (inputType == "update_map")
			parseUpdate_Map();
		else if (inputType == "opponent_moves")
			parseOpponent_Moves();
		else if (inputType == "go")
			parseGo();
		theBot->executeAction();
	}
}

void Parser::parseSetup_Map()
{
#ifdef DEBUG_PRINT
	cout <<"parseSetupMap\n";
#endif // DEBUG_PRINT
	std::string setupType;
	std::cin >> setupType;
	if (setupType == "super_regions")
		parseSuper_Regions();
	if (setupType == "regions")
		parseRegions();
	if (setupType == "neighbors")
		parseNeighbors();
}
void Parser::parseStarting_Regions()
{
#ifdef DEBUG_PRINT
	cout << "parseStartingRegions\n";
#endif // DEBUG_PRINT
	int region;
	int delay;
	std::cin >> delay;
	theBot->startDelay(delay);
	while (std::cin >> region)
	{
		theBot->addStartingRegion(region);
		if (std::cin.peek() == '\n')
			break;
	}
	theBot->setPhase("pickPreferredRegion");
}

void Parser::parseSettings()
{
#ifdef DEBUG_PRINT
	cout << "parseSettings\n";
#endif // DEBUG_PRINT
	std::string settingType;
	std::string bot_name;
	int nbArmies;
	std::cin >> settingType;
	if (settingType == "your_bot")
	{
		std::cin >> bot_name;
		theBot->setBotName(bot_name);
	}
	if (settingType == "opponent_bot")
	{
		std::cin >> bot_name;
		theBot->setOpponentBotName(bot_name);
	}
	if (settingType == "starting_armies")
	{
		std::cin >> nbArmies;
		theBot->setArmiesLeft(nbArmies);
#ifdef DEBUG_PRINT
		cout << "settings starting_armies " << nbArmies << "\n";
#endif // DEBUG_PRINT
	}
}

void Parser::parseUpdate_Map()
{
#ifdef DEBUG_PRINT
	cout <<"parseUpdate_Map\n";
#endif // DEBUG_PRINT
	std::string playerName;
	int noRegion, nbArmies;
	theBot->resetRegionsOwned();
	while (std::cin >> noRegion >> playerName >> nbArmies)
	{
		theBot->updateRegion(noRegion, playerName, nbArmies);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseOpponent_Moves()
{

#ifdef DEBUG_PRINT
	cout << "parseOpponent_Moves\n";
#endif // DEBUG_PRINT
	std::string playerName, action;
	int noRegion, nbArmies, toRegion;
	while (std::cin.peek() != '\n' && std::cin >> playerName >> action)
	{
		if (action == "place_armies")
		{
			std::cin >> noRegion >> nbArmies;
			theBot->addArmies(noRegion, nbArmies);
		}
		if (action == "attack/transfer")
		{
			std::cin >> noRegion >> toRegion >> nbArmies;
			theBot->moveArmies(noRegion, toRegion, nbArmies);
		}
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseGo()
{
	std::string phase;
	int delay;
	std::cin >> phase >> delay;
	theBot->startDelay(delay);
	theBot->setPhase(phase);
}

void Parser::parseSuper_Regions()
{
	int super, reward;
#ifdef DEBUG_PRINT
	std::cout << "parseSuperRegions\n";
#endif // DEBUG_PRINT
	while (std::cin >> super >> reward)
	{
		theBot->addSuperRegion(super, reward);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseRegions()
{
	int super, region;
#ifdef DEBUG_PRINT
	std::cout << "parseRegions\n";
#endif // DEBUG_PRINT
	while (std::cin >> region >> super)
	{
		theBot->addRegion(region, super);
		if (std::cin.peek() == '\n')
			break;
	}
}

void Parser::parseNeighbors()
{
#ifdef DEBUG_PRINT
	std::cout << "parseNeighbors\n";
#endif // DEBUG_PRINT
	int region;
	std::string neighbors;
	std::vector<std::string> neighbors_flds;
	while (std::cin >> region >> neighbors)
	{
		neighbors_flds = splitString(neighbors, ',');
		for (unsigned i = 0; i < neighbors_flds.size(); i++)
			theBot->addNeighbors(region, atoi(neighbors_flds[i].c_str()));
		if (std::cin.peek() == '\n')
			break;
	}
	neighbors_flds.clear();
	theBot->setPhase("findBorders");
}

std::vector<std::string> Parser::splitString(const std::string& string, const char& delimiter)
{
	std::vector<std::string> fields;
	std::string buf = "";
	unsigned i = 0;
	while (i < string.length())
	{
		if (string[i] != delimiter)
			buf += string[i];
		else
		{
			fields.push_back(buf);
			buf = "";
		}
		i++;
	}
	if (!buf.empty())
		fields.push_back(buf);
	return fields;
}

