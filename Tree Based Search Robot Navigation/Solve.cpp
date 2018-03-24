#include "Solve.h"
#include <stack>
#include <queue>
#include <map>
#include <unordered_set>
#include <iostream>

Solve::Solve(Node* s, Node* e) : startPos(s), goalPos(e)
{
}

//N,E,S,W
void Solve::depthFirstSearch()
{
	Node* current = nullptr;
	std::unordered_set<Node*> memory;
	std::stack<Node*> underConsideration;
	std::map<Node*, Node*> path;
	int nodeCountVisited =0;

	underConsideration.push(startPos);
	memory.insert(startPos);
	while (!underConsideration.empty())
	{
		current = underConsideration.top();
		underConsideration.pop();
		nodeCountVisited++;
		for (size_t i = 0; i < 4; i++)
		{
			if (!memory.count(current->getNeighbour(i)) && current->hasNeighbour(i))
			{
				memory.insert(current->getNeighbour(i));
				underConsideration.push(current->getNeighbour(i));
				path[current->getNeighbour(i)] = current;
			}
		}
		if (current == goalPos)
			break;
	}

	while (path.count(current))
	{
		current = path[current];
		std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
	}

	std::cout << nodeCountVisited;

}

void Solve::breadthFirstSearch()
{
	std::unordered_set<Node*> memory;
	std::queue<Node*> underConsideration; //needs a better name
	int nodeCountVisited = 0;

	underConsideration.push(startPos);
	Node* current = nullptr;
	while (!underConsideration.empty())
	{
		current = underConsideration.front();
		underConsideration.pop();
		nodeCountVisited++;

		for (size_t i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{
				underConsideration.push(current->getNeighbour(i));
				memory.insert(current->getNeighbour(i));
			}
		}
		memory.insert(current);
	}
	std::cout << nodeCountVisited;

}
