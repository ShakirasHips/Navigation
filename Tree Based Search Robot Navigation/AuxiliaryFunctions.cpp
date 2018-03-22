#include "AuxiliaryFunctions.h"



std::vector<std::string>& aux::stringParser(std::string & s, char delim, std::vector<std::string>& elems)
{
	s.erase(0, 1);
	s.erase(s.size() - 1);
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;

}

std::vector<int>& aux::stringParser(std::string &s, char delim, std::vector<int> &elems)
{
	s.erase(0, 1);
	s.erase(s.size() - 1);
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(std::stoi(item));
	}
	return elems;

}
