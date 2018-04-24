#pragma once
#include "Node.h"
#include <stack>
#include <unordered_set>

class Solve
{
private:
	Node* startPos;
	Node* goalPos;
	std::vector<Node*> nodesVisted;
	int sizeOfTree;
	int euclid_dist(Node* a, Node* b);
	int manhattan_dist(Node* a, Node* b);
	int RecursiveItterativeSearch(Node* node, int cost, int bound, std::map<Node*, Node*> &currentPath, bool &found);
public:
	Solve(Node* start, Node* ending);


	std::stack<Node*> depthFirstSearch();
	std::stack<Node*> breadthFirstSearch();
	std::stack<Node*> greedyBestFirstSearch();
	std::stack<Node*> AStar();
	std::stack<Node*> bidirectionalSearch();
	std::stack<Node*> iterativeDeepeningAStar();

	int getSizeOfTree() { return sizeOfTree; }
	std::vector<Node*> getNodesVisted() { return nodesVisted; }

	void test();
};

