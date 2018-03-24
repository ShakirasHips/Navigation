#include "Map.h"
#include <iostream>
#define log(x) std::cout << x << std::endl

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
		width = parsedString[0];
		height = parsedString[1];

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
		mapData[parsedString[1]][parsedString[0]] = start;
		parsedString.clear();
		line.clear();
		
		//set ending pos
		std::getline(file, line);
		aux::stringParser(line, ',', parsedString);
		mapData[parsedString[1]][parsedString[0]] = end;
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
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (mapData[i][j] == wall)
				std::cout << "w";
			else if (mapData[i][j] == empty)
				std::cout << "_";
			else if (mapData[i][j] == start)
				std::cout << "s";
			else if (mapData[i][j] == end)
				std::cout << "e";
		}
		std::cout << std::endl;
	}
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

Node* Map::getStartingNode()
{
	return startingNode;
}

Node* Map::getEndingNode()
{
	return endingNode;
}

void Map::GenerateNodes()
{
	for (size_t i = 0; i < width; i++)
	{
		std::vector<Node*> t;
		for (size_t j = 0; j < height; j++)
		{
			if (mapData[i][j] != wall)
			{
				Node* current = new Node(Position(j, i), nullptr, nullptr, nullptr, nullptr);
				t.push_back(current);

				//start and end cant be in wall. hmmmmmm
				if (mapData[i][j] == start)
					startingNode = current;

				if (mapData[i][j] == end)
					endingNode = current;
			}
			else
			{
				t.push_back(nullptr);
			}
		}
		tem.push_back(t);
	}

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (tem[i][j])
			{
				Node* current = tem[i][j];
				if (j != 0) {
					if (tem[i][j - 1])
						current->addWestNode(tem[i][j - 1]);
				}
				if (j != height-1) {
					if (tem[i][j + 1])
						current->addEastNode(tem[i][j + 1]);
				}

				if (i != 0) {
					if (tem[i - 1][j])
						current->addNorthNode(tem[i - 1][j]);
				}

				if (i != width-1) {
					if (tem[i + 1][j])
						current->addSouthNode(tem[i + 1][j]);
				}
			}
			
		}
		
	}
}
