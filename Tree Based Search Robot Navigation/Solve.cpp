#include "Solve.h"
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <math.h>
#define MAX_INT 0x7fffffff
#define STEP_COST 1

//std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
Solve::Solve(Node* s, Node* e) : startPos(s), goalPos(e), sizeOfTree(0)
{
}

std::stack<Node*> Solve::depthFirstSearch()
{
	std::unordered_set<Node*> memory;
	Node* current = nullptr;
	std::stack<Node*> result;
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
	nodesVisted.push_back(current->getNeighbour(i));
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

	underConsideration.push(startPos);
	Node* current = nullptr;
	while (!underConsideration.empty())
	{
		current = underConsideration.front();
		underConsideration.pop();

		for (int i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{
				path[current->getNeighbour(i)] = current;
				underConsideration.push(current->getNeighbour(i));
				memory.insert(current->getNeighbour(i));
				nodesVisted.push_back(current->getNeighbour(i));
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
	sizeOfTree = memory.size();
	return result;

}

int Solve::manhattan_dist(Node* a, Node* b)
{
	return std::abs(b->getPosition().x - a->getPosition().x) +
		std::abs((b->getPosition().y - a->getPosition().y));
}

int Solve::euclid_dist(Node* a, Node* b)
{
	return std::sqrt(((b->getPosition().x - a->getPosition().x)*(b->getPosition().x - a->getPosition().x)
		+ ((b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y))));
}


//Ties the node to its score so it can be sorted in a prio queue
struct Node_fScore_pair
{
	Node* node;
	int fScore;

	Node_fScore_pair() : node(nullptr), fScore(MAX_INT) {}
	Node_fScore_pair(Node* node, int value) : node(node), fScore(value) {};

	//operator so priority_queue stores it in reversed order, then N,W,S,E
	bool operator<(const Node_fScore_pair& right) const
	{

		if (this->fScore == right.fScore)
		{
			if (this->node->getPosition().x - right.node->getPosition().x <= -1)
				return false;
			else if (this->node->getPosition().y - right.node->getPosition().y <= -1)
				return false;
			else if (this->node->getPosition().x - right.node->getPosition().x >= 1)
				return true;
			else if (this->node->getPosition().y - right.node->getPosition().y >= 1)
				return true;
		}
		else
		{
			return this->fScore > right.fScore;
		}
	}
};

std::stack<Node*> Solve::greedyBestFirstSearch()
{
	std::unordered_set<Node*> memory;
	std::priority_queue<Node_fScore_pair> underConsideration;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current = startPos;

	underConsideration.push(Node_fScore_pair(startPos, euclid_dist(startPos, goalPos)));
	memory.insert(startPos);

	while (!underConsideration.empty())
	{
		current = underConsideration.top().node;
		underConsideration.pop();

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
				underConsideration.push(Node_fScore_pair(current->getNeighbour(i), euclid_dist(current->getNeighbour(i), goalPos)));
				memory.insert(current->getNeighbour(i));
				nodesVisted.push_back(current->getNeighbour(i));
				path[current->getNeighbour(i)] = current;

			}
		}
	}
	sizeOfTree = memory.size();
	return result;
}

std::stack<Node*> Solve::AStar()
{
	std::unordered_set<Node*> memory;
	std::priority_queue<Node_fScore_pair> underConsideration;
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
				nodesVisted.push_back(current->getNeighbour(i));

				//This +1 value needs to change if using manhattan dist to +2 or sometimes isn't admissable
				int newCost = costSoFar[current] + STEP_COST;
				if (costSoFar.count(current->getNeighbour(i)))
				{
					if (!costSoFar.count(current->getNeighbour(i)) || newCost < costSoFar[current->getNeighbour(i)])
						continue;
				}
				path[current->getNeighbour(i)] = current;
				costSoFar[current->getNeighbour(i)] = newCost;
				
				underConsideration.push(Node_fScore_pair(current->getNeighbour(i), costSoFar[current->getNeighbour(i)] + euclid_dist(current->getNeighbour(i), goalPos)));

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
				nodesVisted.push_back(startCurrent->getNeighbour(i));
			}

			if (goalCurrent->hasNeighbour(i) && !goalMemory.count(goalCurrent->getNeighbour(i)))
			{
				goalPath[goalCurrent->getNeighbour(i)] = goalCurrent;
				goalUnderConsideration.push(goalCurrent->getNeighbour(i));
				goalMemory.insert(goalCurrent->getNeighbour(i));
				nodesVisted.push_back(goalCurrent->getNeighbour(i));

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

int Solve::search(Node* node, int cost, int bound, std::map<Node*, Node*> &currentPath, bool& found, std::unordered_set<Node*>& memory)
{
	int fCost = cost + euclid_dist(node, goalPos);
	if (fCost > bound)
		return fCost;

	if (node == goalPos)
	{
		found = true;
		return 0;
	}

	int min = -1;
	for (size_t i = 0; i < 4; i++)
	{
		if (node->hasNeighbour(i) && !memory.count(node->getNeighbour(i)))
		{
			int temp = search(node->getNeighbour(i), cost + STEP_COST, bound, currentPath, found, memory);
			currentPath[node->getNeighbour(i)] = node;
			if (found)
			{
				return 0;
			}

			if (temp > min)
			{
				min = temp;
			}
		}
	}
	return min;
}

std::stack<Node*> Solve::iterativeDeepeningAStar()
{
	std::unordered_set<Node*> memory;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	bool found = false;
	int bound = euclid_dist(startPos, goalPos);

	while (true)
	{
		memory.insert(startPos);
		int temp = search(startPos, 0, bound, path, found, memory);

		if (found)
		{
			break;
		}

		if (temp < -1)
			return result;

		bound = temp;
		path.clear();
		memory.clear();
	}

	Node* current = goalPos;
	while (path.count(current))
	{
		result.push(current);
		current = path[current];
		if (current == startPos)
			break;
	}
	result.push(startPos);
	return result;
}

//used to test if Node_fscore_pair was working correctly
void Solve::test()
{
	std::priority_queue<Node_fScore_pair> queue;
	queue.push(Node_fScore_pair(new Node(Position(1, 0), nullptr, nullptr, nullptr, nullptr), 8));
	queue.push(Node_fScore_pair(new Node(Position(1, 2), nullptr, nullptr, nullptr, nullptr), 8));
	queue.push(Node_fScore_pair(new Node(Position(0, 1), nullptr, nullptr, nullptr, nullptr), 8));
	queue.push(Node_fScore_pair(new Node(Position(2, 1), nullptr, nullptr, nullptr, nullptr), 8));
	queue.push(Node_fScore_pair(new Node(Position(5, 4), nullptr, nullptr, nullptr, nullptr), 6));

	while (!queue.empty())
	{
		Node* current = queue.top().node;
		queue.pop();
		std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
	}


}


