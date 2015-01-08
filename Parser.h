#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

//stl
#include <stdio.h>
#include <string>
#include <vector>

// 3rdparty
#include <3rdparty/boost/noncopyable.hpp>


class Bot;

class Parser : boost::noncopyable
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
    void parseWastelands();

private:
    Parser();
	Bot* theBot;

};

#endif // PARSER_H_INCLUDED
