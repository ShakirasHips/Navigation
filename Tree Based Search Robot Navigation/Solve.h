#pragma once
#include "Map.h"

class Solve
{
private:
	Node* startPos;
	Node* goalPos;
public:
	Solve(Node* start, Node* ending);


	void depthFirstSearch();
	void breadthFirstSearch();
};

