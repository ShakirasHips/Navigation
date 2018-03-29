#include <iostream>
#include "Map.h"
#include "Node.h"
#include "Solve.h"
#include "bitmap\bitmap_image.hpp"
#include "AuxiliaryFunctions.h"
#define log(x) std::cout << x << std::endl
#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"
#define filepath2 "C:/Users/Jayden/Desktop/Untitled.bmp"

int main(int argc, char** argv)
{
	Map map;
	map.loadMap(filepath2);
	map.printMap();
	map.GenerateNodes();
	Solve solver(map.getStartingNode(), map.getEndingNode());
	aux::printStack(solver.depthFirstSearch());



	std::cin.get();
	return 0;
}