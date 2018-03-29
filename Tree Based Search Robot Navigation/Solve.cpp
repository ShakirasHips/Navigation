#include "Solve.h"
#include <queue>
#include <map>
#include <unordered_set>
#include <iostream>

Solve::Solve(Node* s, Node* e) : startPos(s), goalPos(e)
{
}

std::stack<Node*> Solve::depthFirstSearch()
{
	Node* current = nullptr;
	std::stack<Node*> result;
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
		{
			result.push(current);
			while (path.count(current))
			{
				current = path[current];
				result.push(current);
			}
			break;
		}
	}
	return result;
}

std::stack<Node*> Solve::breadthFirstSearch()
{
	std::unordered_set<Node*> memory;
	std::queue<Node*> underConsideration; //needs a better name
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
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
				path[current->getNeighbour(i)] = current;
				underConsideration.push(current->getNeighbour(i));
				memory.insert(current->getNeighbour(i));
			}
		}
		memory.insert(current);

		if (current == goalPos)
		{
			result.push(current);
			while (path.count(current))
			{
				current = path[current];
				result.push(current);
			}
			break;
		}
	}
	return result;

}

std::stack<Node*> Solve::AStar()
{
	
}
