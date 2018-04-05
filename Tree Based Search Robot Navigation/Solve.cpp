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


int euclid_dist_sqr(int x0, int x1, int y0, int y1)
{
	return std::abs((x1 - x0)) + std::abs((y1 - y0));
	//return ((x1 - x0)*(x1 - x0)) + ((y1 - y0) * (y1 - y0));
}

std::stack<Node*> Solve::AStar()
{
	std::unordered_set<Node*> memory;
	std::unordered_set<Node*> underConsideration;
	std::map<Node*, int> gScore;
	std::map<Node*, int> fScore;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current = nullptr;
	underConsideration.insert(startPos);
	gScore[startPos] = 0.0f;
	fScore[startPos] = euclid_dist_sqr(startPos->getPosition().x, goalPos->getPosition().x, startPos->getPosition().y, goalPos->getPosition().y);
	//current = startPos;
	
	while (!underConsideration.empty())
	{
		std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
		for (auto value: underConsideration)
		{		
			if (fScore[current] > fScore[value])
				current = value;
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
			

		underConsideration.erase(current);
		memory.insert(current);
		for (size_t i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{
				underConsideration.insert(current->getNeighbour(i));

				int tentativce_gScore = gScore[current] + 1;
				if (gScore.count(current->getNeighbour(i)))
				{
					if (tentativce_gScore >= gScore[current->getNeighbour(i)])
						continue;
				}
				path[current->getNeighbour(i)] = current;
				gScore[current->getNeighbour(i)] = tentativce_gScore;
				fScore[current->getNeighbour(i)] = gScore[current] + euclid_dist_sqr(current->getNeighbour(i)->getPosition().x, goalPos->getPosition().x, current->getNeighbour(i)->getPosition().y, goalPos->getPosition().y);
			}
		}
	}


	return result;
}
