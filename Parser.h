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
	void parseSetupMap();
	void parseStartingRegions();
	void parseSettings();
	void parseUpdateMap();
	void parseOpponentMoves();
	void parseGo();
	void parseSuperRegions();
	void parseRegions();
	void parseNeighbors();

private:
	std::vector<std::string> splitString(const std::string& string, const char& delimiter);

	Bot* theBot;

};

#endif // PARSER_H_INCLUDED
