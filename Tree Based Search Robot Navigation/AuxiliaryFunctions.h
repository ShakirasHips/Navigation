#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include "Node.h"

class Node;
namespace aux
{
	//splits strings
	std::vector<std::string> &stringParser(std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<int> &stringParser(std::string &s, char delim, std::vector<int> &elems);

	void printStack(std::stack<Node*>);
}
