#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

//stl
#include <stdio.h>
#include <string>
#include <vector>

class Bot;

class Parser
{
public:
	Parser(Bot* bot);
	virtual ~Parser();

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

private:
	std::vector<std::string>& splitString(std::string String, std::vector<std::string>& flds, char delim);

	Bot* theBot;

};

#endif // PARSER_H_INCLUDED
