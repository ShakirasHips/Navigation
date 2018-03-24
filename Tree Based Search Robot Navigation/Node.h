#pragma once
#include <map>
#include "AuxiliaryFunctions.h"

//0= North; 1=south; 2=east; 3= west;
class Node
{
private: 
	Position position;
	Node* Neighbours[4];
public:
	Node(Position, Node* n, Node* s, Node* e, Node* w);
	~Node();

	Position getPosition();
	bool hasNeighbour(Directions);
	bool hasNeighbour(int i);
	Node* getNeighbour(Directions);
	Node* getNeighbour(int);

	void addNorthNode(Node*);
	void addSouthNode(Node*);
	void addEastNode(Node*);
	void addWestNode(Node*);

	Node* getNeighbors();
};

