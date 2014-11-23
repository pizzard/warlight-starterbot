#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <stdio.h>

#include <string>
#include <vector>
class Bot;
class Parser
{
    Bot* theBot;

    public:
        Parser();
        virtual ~Parser();
        void initParser(Bot* bot);
        void parseInput();
        void parseSetup_Map();
        void parseStarting_Regions();
        void parseSettings();
        void parseUpdate_Map();
        void parseOpponent_Moves();
        void parseGo();
        void parseSuper_Regions();
        void parseRegions();
        void parseNeighbors();
    protected:
    private:
        std::vector<std::string>& splitString(std::string String, std::vector<std::string>& flds, char delim);
};

#endif // PARSER_H_INCLUDED
