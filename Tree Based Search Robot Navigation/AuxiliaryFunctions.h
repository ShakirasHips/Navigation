#pragma once
#include <vector>
#include <string>
#include <sstream>

enum mapElements
{
	empty,
	wall,
	start,
	end,
};

enum Directions
{
	North,
	South,
	East,
	West,
};

struct Position
{
	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

namespace aux
{
	//splits strings
	std::vector<std::string> &stringParser(std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<int> &stringParser(std::string &s, char delim, std::vector<int> &elems);
}
