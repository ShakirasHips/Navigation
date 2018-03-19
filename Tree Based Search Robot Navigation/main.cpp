#include <iostream>
#include "Map.h"

#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"


int main(int argc, char** argv)
{
	Map map;
	if (map.loadMap(filepath))
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;

	std::cin.get();
	return 0;
}