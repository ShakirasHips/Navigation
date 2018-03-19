#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace aux
{
	//splits strings
	std::vector<std::string> &stringParser(std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<int> &stringParser(std::string &s, char delim, std::vector<int> &elems);
}
