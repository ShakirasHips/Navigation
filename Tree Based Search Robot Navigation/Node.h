#pragma once
#include <map>
#include "AuxiliaryFunctions.h"

struct Position
{
	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};
	int x;
	int y;
};

enum Directions
{
	North,
	South,
	East,
	West,
};

//0= North; 1=south; 2=east; 3= west;
class Node
{
private: 
	Position position;
	Node* Neighbours[4];
public:
	Node() {};
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

