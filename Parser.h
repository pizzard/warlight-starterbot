#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

//stl
#include <stdio.h>
#include <string>
#include <vector>

// project
#include "main.h"

class Bot;

class Parser: boost::noncopyable
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
	void parsePickStartingRegion();
	void parseOpponentStartingRegions();
	void parseNeighbors();
	void parseWastelands();

private:
	Parser();
	Bot* theBot;

	// helper function for the case we want to handle \r\n in future
	inline bool lineEnds(){ return bool(std::cin.peek() == '\n'); }

};

#endif // PARSER_H_INCLUDED
