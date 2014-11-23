#include "Parser.h"
#include <iostream>
#include <stdlib.h>
#include "Bot.h"

using namespace std;

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

void Parser::initParser(Bot* bot)
{
    theBot = bot;
}

void Parser::parseInput()
{
    string inputType;
    while (cin >> inputType)
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
    string setupType;
    cin >> setupType;
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
    cin >> delay;
    theBot->startDelay(delay);
    while(cin  >> region )
    {
        theBot->addStartingRegion(region);
        if (cin.peek()== '\n')
            break;
    }
    theBot->setPhase("pickPreferredRegion");
}

void Parser::parseSettings()
{
#ifdef DEBUG_PRINT
    cout << "parseSettings\n";
#endif // DEBUG_PRINT
    string settingType;
    string bot_name;
    int nbArmies;
    cin >> settingType;
    if (settingType == "your_bot")
    {
        cin >> bot_name;
        theBot->setBotName(bot_name);
    }
    if (settingType == "opponent_bot")
    {
        cin >> bot_name;
        theBot->setOpponentBotName(bot_name);
    }
    if (settingType == "starting_armies")
    {
        cin >> nbArmies;
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
    string playerName;
    int noRegion, nbArmies;
    theBot->resetRegionsOwned();
    while (cin >> noRegion >> playerName >> nbArmies)
    {
        theBot->updateRegion(noRegion,playerName,nbArmies);
        if (cin.peek()== '\n')
            break;
    }
}

void Parser::parseOpponent_Moves()
{

#ifdef DEBUG_PRINT
    cout << "parseOpponent_Moves\n";
#endif // DEBUG_PRINT
    string playerName, action;
    int noRegion, nbArmies, toRegion;
    while (cin.peek()!= '\n' && cin >> playerName >> action)
    {
        if (action == "place_armies")
        {
            cin >> noRegion >> nbArmies;
            theBot->addArmies(noRegion,nbArmies);
       }
        if (action == "attack/transfer")
        {
            cin >> noRegion >> toRegion >> nbArmies;
            theBot->moveArmies(noRegion,toRegion,nbArmies);
       }
        if (cin.peek()== '\n')
            break;
    }
}

void Parser::parseGo()
{
    string phase;
    int delay;
    cin >> phase >> delay;
    theBot->startDelay(delay);
    theBot->setPhase(phase);
}

void Parser::parseSuper_Regions()
{
    int super,reward;
#ifdef DEBUG_PRINT
    cout << "parseSuperRegions\n";
#endif // DEBUG_PRINT

    while(cin >> super >> reward)
    {
         theBot->addSuperRegion(super,reward);
        if (cin.peek()== '\n')
            break;
    }
}

void Parser::parseRegions()
{
    int super,region;
#ifdef DEBUG_PRINT
    cout << "parseRegions\n";
#endif // DEBUG_PRINT

    while(cin  >> region >> super)
    {
        theBot->addRegion(region,super);
        if (cin.peek()== '\n')
            break;
    }
}

void Parser::parseNeighbors()
{
#ifdef DEBUG_PRINT
    cout <<  "parseNeighbors\n";
#endif // DEBUG_PRINT
    int region;
    string neighbors;
    vector<string> neighbors_flds;
    while(cin  >> region >> neighbors )
    {
        neighbors_flds = splitString(neighbors, neighbors_flds, ',');
        for (unsigned i = 0; i < neighbors_flds.size(); i++)
            theBot->addNeighbors(region, atoi(neighbors_flds[i].c_str()));
        if (cin.peek()== '\n')
            break;
    }
    neighbors_flds.clear();
    theBot->setPhase("findBorders");
}

vector<string>& Parser::splitString(string String, vector<string>& flds, char delim)
{
    if (!flds.empty())
        flds.clear();
    string buf = "";
    unsigned i = 0;
    while (i < String.length())
    {
        if (String[i] != delim)
            buf += String[i];
        else
        {
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}


