#include <iostream>
#include "Map.h"
#include "Node.h"


#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"


int main(int argc, char** argv)
{
	Map map;
	map.loadMap(filepath);
	map.printMap();
	Node node(Position(1, 2), nullptr, nullptr, nullptr, nullptr);
	std::cin.get();
	return 0;
}