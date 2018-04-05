#include "Node.h"


Node::Node(Position pos, Node* north, Node* south, Node* east, Node* west)
{
	position = pos;
	Neighbours[North] = north;
	Neighbours[South] = south;
	Neighbours[East] = east;
	Neighbours[West] = west;
}

Node::~Node()
{
}

Position Node::getPosition()
{
	return position;
}


//hmmmmm
bool Node::hasNeighbour(Directions d)
{
	return Neighbours[d];
}

bool Node::hasNeighbour(int i)
{
	if (Neighbours[i] == nullptr)
		return false;
	else
		return true;
}

//thinking emoji
Node* Node::getNeighbour(Directions d)
{
	return Neighbours[d];
}

Node * Node::getNeighbour(int i)
{
	return Neighbours[i];
}

void Node::addNorthNode(Node* node)
{
	Neighbours[North] = node;
}

void Node::addSouthNode(Node* node)
{
	Neighbours[South] = node;
}

void Node::addEastNode(Node* node)
{
	Neighbours[East] = node;
}

void Node::addWestNode(Node* node)
{
	Neighbours[West] = node;
}

Node* Node::getNeighbors()
{
	return *Neighbours;
}
