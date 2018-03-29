#include "Map.h"
#include <iostream>
#include "bitmap\bitmap_image.hpp"
#define log(x) std::cout << x << std::endl

Map::Map()
{

}

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

	for (size_t x = 0; x < width; x++)
	{
		std::vector<mapElements> temp;
		for (size_t y = 0; y < height; y++)
		{
			rgb_t colour;
			//log(x);
			//log(y);
			image.get_pixel(x, y, colour);

			if (colour == white)
			{
				temp.push_back(empty);
			}
			else if (colour == black)
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
		}
		mapData.push_back(temp);
	}
	return true;
}

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


//TODO: optimise for straight lines remove unnessessary nodes
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
