#include "Map.h"
#include <iostream>
#include "bitmap\bitmap_image.hpp"
#define log(x) std::cout << x << std::endl

Map::Map()
{

}

//the default function that should be called, calls other loaders depending on filetype
bool Map::loadMap(std::string filepath)
{
	if (filepath.substr(filepath.size() - 3) == "txt")
	{
		return this->loadTextfile(filepath);
	}
	else if (filepath.substr(filepath.size() - 3) == "bmp")
	{
		return this->loadBitmap(filepath);
	}
	return false;
}

/**
* Load 24bit bitmap file
* Red 255 pixel is ending node
* Green 255 pixel is starting node
* Black 0,0,0 is walls
* anthing else is movable space
**/
bool Map::loadBitmap(std::string filepath)
{
	bitmap_image image(filepath);

	if (!image)
	{
		return false;
	}

	width = image.width();
	height = image.height();
	rgb_t white = make_colour(255, 255, 255);
	rgb_t black = make_colour(0, 0, 0);
	rgb_t red = make_colour(255, 0, 0);
	rgb_t green = make_colour(0, 255, 0);

	for (size_t y = 0; y < height; y++)
	{
		std::vector<mapElements> temp;
		for (size_t x = 0; x < width; x++)
		{
			rgb_t colour;
			image.get_pixel(x, y, colour);

			if (colour == black)
			{
				temp.push_back(wall);
			}
			else if (colour == green)
			{
				temp.push_back(start);
			}
			else if (colour == red)
			{
				temp.push_back(end);
			}
			else
			{
				temp.push_back(empty);
			}
		}
		mapData.push_back(temp);
	}
	return true;
}

//Loads from text file using that format set up in the assignment
bool Map::loadTextfile(std::string filepath)
{
	std::fstream file;
	file.open(filepath, std::ios::in, std::ios::binary);

	if (file.is_open())
	{
		std::string line;
		std::vector<int> parsedString;
		std::getline(file, line);
		aux::stringParser(line, ',', parsedString);
		width = parsedString[1];
		height = parsedString[0];

		//Create the map and fill it with nothingness
		for (size_t y  = 0; y < height; y++)
		{
			std::vector<mapElements> temp;
			for (size_t x = 0; x < width; x++)
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
					mapData[parsedString[1] + j][parsedString[0] + i]= wall;
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

//print map to console, mostly used for testing the map loaded correctly
void Map::printMap()
{
	for (auto& rows: mapData)
	{
		for (auto& index: rows)
		{
			if (index == wall)
				std::cout << "w";
			else if (index == empty)
				std::cout << "_";
			else if (index == start)
				std::cout << "s";
			else if (index == end)
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


//Generate nodes and links them up to there neighbors
//map is set up like this just in case i want to "compress" the map or perform some sort of pre-process on it
//also clears mapData to conserve on memeory at the end
void Map::GenerateNodes()
{
	for (size_t y = 0; y < height; y++)
	{
		std::vector<Node*> t;
		for (size_t x = 0; x < width; x++)
		{
			if (mapData[y][x] != wall)
			{
				Node* current = new Node(Position(x, y), nullptr, nullptr, nullptr, nullptr);
				t.push_back(current);

				if (mapData[y][x] == start)
					startingNode = current;

				if (mapData[y][x] == end)
					endingNode = current;
			}
			else
			{
				t.push_back(nullptr);
			}
		}
		nodeContainer.push_back(t);
	}

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (nodeContainer[y][x])
			{
				Node* current = nodeContainer[y][x];
				if (x != 0) {
					if (nodeContainer[y][x - 1])
						current->addWestNode(nodeContainer[y][x - 1]);
				}
				if (x != width-1) {
					if (nodeContainer[y][x + 1])
						current->addEastNode(nodeContainer[y][x + 1]);
				}

				if (y != 0) {
					if (nodeContainer[y - 1][x])
						current->addNorthNode(nodeContainer[y - 1][x]);
				}

				if (y != height-1) {
					if (nodeContainer[y + 1][x])
						current->addSouthNode(nodeContainer[y + 1][x]);
				}
			}
			
		}
		
	}
	mapData.clear();
}
