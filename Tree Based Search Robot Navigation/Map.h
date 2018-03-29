#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "AuxiliaryFunctions.h"
#include "Node.h"

class Map
{
private:
	int width, height;
	Node* startingNode;
	Node* endingNode;
	std::vector<std::vector<mapElements>> mapData;
	std::vector<std::vector<Node*>> tem;
public:
	Map();

	bool loadMap(std::string filePath);
	bool loadBitmap(std::string filepath);
	bool loadTextfile(std::string filepath);
	void printMap();

	int getWidth();
	int getHeight();
	Node* getStartingNode();
	Node* getEndingNode();


	void GenerateNodes();

};

