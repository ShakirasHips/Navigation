#include <iostream>
#include "Map.h"
#include "Node.h"
#include "Solve.h"
#define log(x) std::cout << x << std::endl
#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"


int main(int argc, char** argv)
{
	Map map;
	map.loadMap(filepath);
	map.printMap();
	map.GenerateNodes();
	Solve solver(map.getStartingNode(), map.getEndingNode());
	solver.depthFirstSearch();
	std::cin.get();
	return 0;
}