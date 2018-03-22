#include "Node.h"


Node::Node(Position pos, Node* north, Node* south, Node* east, Node* west)
{
	position = pos;
	Neighbours.insert_or_assign(North, north);
	Neighbours.insert_or_assign(South, south);
	Neighbours.insert_or_assign(East, east);
	Neighbours.insert_or_assign(West, west);
}

Node::~Node()
{
}
