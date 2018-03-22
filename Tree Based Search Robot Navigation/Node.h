#pragma once
#include <map>
#include "AuxiliaryFunctions.h"

class Node
{
private: 
	Position position;
	std::map<Directions, Node*> Neighbours;
public:
	Node(Position, Node*, Node*, Node*, Node*);
	~Node();
};

