#include "Solve.h"
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <math.h>
#define MAX_INT 0x7fffffff
//std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
Solve::Solve(Node* s, Node* e) : startPos(s), goalPos(e), sizeOfTree(0)
{
}

std::stack<Node*> Solve::depthFirstSearch()
{
	Node* current = nullptr;
	std::stack<Node*> result;
	std::unordered_set<Node*> memory;
	std::stack<Node*> underConsideration;
	std::map<Node*, Node*> path;

	underConsideration.push(startPos);
	memory.insert(startPos);
	while (!underConsideration.empty())
	{
		current = underConsideration.top();
		memory.insert(current);
		underConsideration.pop();
		for (int i = 3; i >= 0; i--)
		{
			if (!memory.count(current->getNeighbour(i)) && current->hasNeighbour(i))
			{
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

	sizeOfTree = memory.size();
	return result;
}

std::stack<Node*> Solve::breadthFirstSearch()
{
	std::unordered_set<Node*> memory;
	std::queue<Node*> underConsideration; 
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
			
		for (int i = 3; i >= 0; i--)
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
	sizeOfTree = memory.size() + underConsideration.size();
	return result;

}

int manhattan_dist(Node* a, Node* b)
{
	return std::abs(b->getPosition().x - a->getPosition().x) + 
		std::abs((b->getPosition().y - a->getPosition().y));
}

int euclid_dist(Node* a, Node* b)
{
	return std::sqrt(((b->getPosition().x - a->getPosition().x)*(b->getPosition().x - a->getPosition().x)
	+ ((b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y))));
}

//TODO: change this to prio que
std::stack<Node*> Solve::greedyBestFirstSearch()
{
	std::unordered_set<Node*> underConsideration;
	std::unordered_set<Node*> memory;
	std::map<Node*, float> nodeScore;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current = startPos;

	underConsideration.insert(startPos); 
	memory.insert(startPos);
	nodeScore[startPos] = euclid_dist(startPos, goalPos);

	while (!underConsideration.empty())
	{
		bool first = false;
		for (auto node: underConsideration)
		{
			if (nodeScore[node] < nodeScore[current] || !first)
				current = node;

			first = true;
		}
		underConsideration.erase(current);

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

		for (size_t i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{
				underConsideration.insert(current->getNeighbour(i));
				memory.insert(current->getNeighbour(i));
				path[current->getNeighbour(i)] = current;
				nodeScore[current->getNeighbour(i)] = euclid_dist(current->getNeighbour(i), goalPos);

			}
		}
	}
	sizeOfTree = memory.size();
	return result;
}

std::stack<Node*> Solve::AStar()
{
	//Ties the node to its score so it can be sorted in a prio queue
	struct Node_fScore_pair
	{
		Node* node;
		int fScore;

		Node_fScore_pair() : node(nullptr), fScore(MAX_INT) {}
		Node_fScore_pair(Node* node, int value) : node(node), fScore(value) {};

		//rev operator so prio que stores it in rev order
		bool operator<(const Node_fScore_pair& right) const
		{
			return this->fScore > right.fScore;
		}
	};

	std::priority_queue<Node_fScore_pair> underConsideration;
	std::unordered_set<Node*> memory;
	std::map<Node*, int> costSoFar;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current;
	
	underConsideration.push(Node_fScore_pair(startPos, euclid_dist(startPos, goalPos)));
	memory.insert(startPos);
	costSoFar[startPos] = 0;
	bool foundSolution = false;

	while (!underConsideration.empty())
	{
		current = underConsideration.top().node;
		underConsideration.pop();

		if (current == goalPos)
		{
			foundSolution = true;
			result.push(current);
			while (path.count(current))
			{
				current = path[current];
				result.push(current);
			}
			break;
		}
			
		for (size_t i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{	
				memory.insert(current->getNeighbour(i));

				//This +1 value needs to change if using manhattan dist to +2 or sometimes isn't admissable
				int newCost = costSoFar[current] + 1;
				if (costSoFar.count(current->getNeighbour(i)))
				{
					if (!costSoFar.count(current->getNeighbour(i)) || newCost < costSoFar[current->getNeighbour(i)])
						continue;
				}
				path[current->getNeighbour(i)] = current;
				costSoFar[current->getNeighbour(i)] = newCost;
				
				underConsideration.push(Node_fScore_pair(current->getNeighbour(i), costSoFar[current] + euclid_dist(current->getNeighbour(i), goalPos)));

			}
		}
	}

	if (!foundSolution)
	{
		sizeOfTree = memory.size();
		return result;
	}

	while (path.count(current))
	{
		current = path[current];
		result.push(current);
	}
	sizeOfTree = memory.size();
	return result;
}

//Expands both nodes and checks to see if they have a common node
std::stack<Node*> Solve::bidirectionalSearch()
{
	std::unordered_set<Node*> startMemory, goalMemory;
	std::queue<Node*> startUnderConsideration, goalUnderConsideration;
	std::unordered_map<Node*, Node*> startPath, goalPath;
	std::stack<Node*> result;
	Node* startCurrent = nullptr;
	Node* goalCurrent = nullptr;

	startUnderConsideration.push(startPos);
	goalUnderConsideration.push(goalPos);

	startMemory.insert(startPos);
	goalMemory.insert(goalPos);

	Node* commonNode = nullptr;
	bool foundSolution = false;
	
	while (!startUnderConsideration.empty() && !goalUnderConsideration.empty())
	{
		startCurrent = startUnderConsideration.front();
		goalCurrent = goalUnderConsideration.front();
		startUnderConsideration.pop();
		goalUnderConsideration.pop();
		
		for (size_t i = 0; i < 4; i++)
		{
			if (startCurrent->hasNeighbour(i) && !startMemory.count(startCurrent->getNeighbour(i)))
			{
				startPath[startCurrent->getNeighbour(i)] = startCurrent;
				startUnderConsideration.push(startCurrent->getNeighbour(i));
				startMemory.insert(startCurrent->getNeighbour(i));
			}

			if (goalCurrent->hasNeighbour(i) && !goalMemory.count(goalCurrent->getNeighbour(i)))
			{
				goalPath[goalCurrent->getNeighbour(i)] = goalCurrent;
				goalUnderConsideration.push(goalCurrent->getNeighbour(i));
				goalMemory.insert(goalCurrent->getNeighbour(i));
			}
		}

		if (startMemory.count(goalCurrent))
		{
			commonNode = goalCurrent;
			foundSolution = true;
			break;
		}
	}
	
	if (!foundSolution)
	{
		sizeOfTree = startMemory.size() + goalMemory.size();
		return result;
	}
		

	std::stack<Node*> temp;
	goalCurrent = commonNode;
	while (goalPath.count(goalCurrent))
	{
		goalCurrent = goalPath[goalCurrent];
		temp.push(goalCurrent);
	}
	while (!temp.empty())
	{
		result.push(temp.top());
		temp.pop();
	}


	startCurrent = commonNode;
	while (startPath.count(startCurrent))
	{
		result.push(startCurrent);
		startCurrent = startPath[startCurrent];
	}
	result.push(startPos);

	sizeOfTree = startMemory.size() + goalMemory.size();
	return result;
}

int Solve::search(std::stack<Node*> underConsideration, int cost, int bound, std::map<Node*, Node*> &currentPath, std::unordered_set<Node*>& memory)
{

	Node* current = underConsideration.top();
	int fCost = cost + manhattan_dist(current, goalPos);
	
	if (fCost > bound)
		return fCost;

	if (current == goalPos)
		return -1;

	int min = MAX_INT;
	for (size_t i = 0; i < 4; i++)
	{
		if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
		{
			underConsideration.push(current->getNeighbour(i));
			currentPath[current->getNeighbour(i)] = current;
			memory.insert(current);

			//std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
			int t = search(underConsideration, cost + 1, bound, currentPath, memory);

			if (t == -1)
				return -1;

			if (t < min)
				min = t;

			if (!underConsideration.empty())
			{
				underConsideration.pop();
			}

		}
	}
	return min;
}

std::stack<Node*> Solve::iterativeDeepeningAStar()
{
	std::stack<Node*> underConsideration;
	std::unordered_set<Node*> memory;
	std::map<Node*, int> costSoFar;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current;

	int bound = manhattan_dist(startPos, goalPos);
	underConsideration.push(startPos);
	memory.insert(startPos);

	while (true)
	{
		int t = search(underConsideration, 0, bound, path, memory);

		if (t == -1)
			break;

		if (t == MAX_INT)
			return result;

		bound = t;
	}

	current = goalPos;
	while (path.count(current))
	{
		//std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
		result.push(current);
		current = path[current];
	}
	result.push(startPos);
	return result;
}


