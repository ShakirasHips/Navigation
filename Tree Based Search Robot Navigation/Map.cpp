#include "Map.h"
#include <iostream>
#define log(x) std::cout << x << std::endl;

Map::Map()
{

}

bool Map::loadMap(std::string filePath)
{
	std::fstream file;
	file.open(filePath, std::ios::in, std::ios::binary);

	if (file.is_open())
	{
		std::string line;
		std::vector<int> parsedString;
		std::getline(file, line);
		aux::stringParser(line, ',', parsedString);

		//Create the map and fill it with nothingness
		for (size_t i = 0; i < parsedString[0]; i++)
		{
			std::vector<mapElements> temp;
			for (size_t j = 0; j < parsedString[1]; j++)
			{
				temp.push_back(empty);
			}
			mapData.push_back(temp);
		}
		parsedString.clear();
		line.clear();
		
		//set starting pos
		std::getline(file, line);
		aux::stringParser(line, ',', parsedString);
		startingPosition = Position(parsedString[0], parsedString[1]);
		parsedString.clear();
		line.clear();
		
		//set ending pos
		std::getline(file, line);
		aux::stringParser(line, ',', parsedString);
		endPosition = Position(parsedString[0], parsedString[1]);
		parsedString.clear();
		line.clear();

		//set up walls
		while (std::getline(file, line))
		{
			aux::stringParser(line, ',', parsedString);

			for (size_t i = 0; i < parsedString[2]; i++)
			{
				for (size_t j = 0; j < parsedString[3]; j++)
				{
					mapData[parsedString[1] + j][parsedString[0] + i] = wall;
				}
			}
			parsedString.clear();
			line.clear();
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Map::printMap()
{
	for (auto data: mapData) 
	{
		for (auto elements : data)
		{
			if (elements == wall)
				std::cout << "w";
			else if (elements == empty)
				std::cout << "_";
		}
		std::cout << std::endl;
	}
}
