#pragma once
#include "Node.h"
#include <stack>

class Solve
{
private:
	Node* startPos;
	Node* goalPos;
public:
	Solve(Node* start, Node* ending);


	std::stack<Node*> depthFirstSearch();
	std::stack<Node*> breadthFirstSearch();
	std::stack<Node*> greedyBestFirstSearch();
	std::stack<Node*> AStar();

	std::stack<Node*> bidirectionalSearch();
};

