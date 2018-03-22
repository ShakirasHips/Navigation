#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "AuxiliaryFunctions.h"

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

