#include <iostream>
#include "Map.h"
#include "Node.h"
#include "Solve.h"
#include "bitmap\bitmap_image.hpp"
#include "AuxiliaryFunctions.h"
#define log(x) std::cout << x << std::endl
#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"
#define filepath2 "C:/Users/Jayden/Desktop/newermaze.bmp"

int main(int argc, char** argv)
{
	Map map;
	map.loadMap(filepath2);
	map.GenerateNodes();
	Solve solver(map.getStartingNode(), map.getEndingNode());
	//aux::printStack(solver.bidirectionalSearch());
	aux::drawPath(solver.bidirectionalSearch(), filepath2, "C:/Users/Jayden/Desktop/lol.bmp" );


	/*Map map;
	std::string searchAlg(argv[2]);
	map.loadMap(argv[1]);
	map.GenerateNodes();
	Solve solver(map.getStartingNode(), map.getEndingNode());



	if (searchAlg == "bfs")
		aux::drawPath(solver.breadthFirstSearch(), argv[1], argv[3]);

	if (searchAlg == "dfs")
		aux::drawPath(solver.depthFirstSearch(), argv[1], argv[3]);
*/
	std::cin.get();
	return 0;
}