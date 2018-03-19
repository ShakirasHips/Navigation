#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "AuxiliaryFunctions.h"

struct Position
{
	Position() : x(0), y(0) {};
	Position(int x, int y): x(x),y(y) {};
	int x;
	int y;
};
enum mapElements 
{
	empty,
	wall,
};

class Map
{
private:
	Position startingPosition;
	Position endPosition;
	std::vector<std::vector<mapElements>> mapData;
public:
	Map();

	bool loadMap(std::string filePath);
	void printMap();

};

