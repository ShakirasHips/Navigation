#pragma once
#include "Node.h"
#include <stack>
#include <unordered_set>

class Solve
{
private:
	Node* startPos;
	Node* goalPos;
	int sizeOfTree;
	int search(std::stack<Node*> path, int cost, int bound, std::map<Node*, Node*> &current, std::unordered_set<Node*> &memeory);
public:
	Solve(Node* start, Node* ending);


	std::stack<Node*> depthFirstSearch();
	std::stack<Node*> breadthFirstSearch();
	std::stack<Node*> greedyBestFirstSearch();
	std::stack<Node*> AStar();
	std::stack<Node*> bidirectionalSearch();
	std::stack<Node*> iterativeDeepeningAStar();

	int getSizeOfTree() { return sizeOfTree; }

};

