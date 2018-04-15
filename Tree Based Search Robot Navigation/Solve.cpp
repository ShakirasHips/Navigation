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

float euclid_dist_sqr(Node* a, Node* b)
{
	//return std::abs((x1 - x0)) + std::abs((y1 - y0));
	return ((b->getPosition().x - a->getPosition().x)*(b->getPosition().x - a->getPosition().x) + ((b->getPosition().y - a->getPosition().y) * (b->getPosition().y - a->getPosition().y)));
}

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
	nodeScore[startPos] = euclid_dist_sqr(startPos, goalPos);

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
				nodeScore[current->getNeighbour(i)] = euclid_dist_sqr(current->getNeighbour(i), goalPos);

			}
		}
	}
	return result;
}

//TODO: fix this
std::stack<Node*> Solve::AStar()
{
	std::unordered_set<Node*> underConsideration;
	std::unordered_set<Node*> memory;
	std::map<Node*, float> costSoFar;
	std::map<Node*, float> fScore;
	std::map<Node*, Node*> path;
	std::stack<Node*> result;
	Node* current = startPos;
	
	underConsideration.insert(startPos);
	memory.insert(startPos);
	costSoFar[startPos] = 0.0f;
	fScore[startPos] = euclid_dist_sqr(startPos, goalPos);
	
	while (!underConsideration.empty())
	{
		bool first = false;
		for (auto node: underConsideration)
		{
			
			//std::cout << fScore[node] << std::endl;
			
			if (fScore[node] < fScore[current] || !first)
				current = node;

			first = true;
		}

		//std::cout << current->getPosition().x << ", " << current->getPosition().y << std::endl;
		underConsideration.erase(current);

		/*if (current == goalPos)
		{
			result.push(current);
			while (path.count(current))
			{
				current = path[current];
				result.push(current);
			}
			break;
		}*/
			
		for (size_t i = 0; i < 4; i++)
		{
			if (current->hasNeighbour(i) && !memory.count(current->getNeighbour(i)))
			{	
				underConsideration.insert(current->getNeighbour(i));
				memory.insert(current->getNeighbour(i));
				float newCost = costSoFar[current] + 1;
				if (costSoFar.count(current->getNeighbour(i)))
				{
					if (!costSoFar.count(current->getNeighbour(i)) || newCost < costSoFar[current->getNeighbour(i)])
						continue;
				}
				path[current->getNeighbour(i)] = current;
				costSoFar[current->getNeighbour(i)] = newCost;
				fScore[current->getNeighbour(i)] = costSoFar[current] + euclid_dist_sqr(current->getNeighbour(i), goalPos);

			}
		}
	}

	result.push(current);
	while (path.count(current))
	{
		current = path[current];
		result.push(current);
	}

	return result;
}

std::stack<Node*> Solve::bidirectionalSearch()
{
	std::unordered_set<Node*> startMemory, goalMemory;
	std::map<int, std::unordered_set<Node*>> depth_nodes_pair_start, depth_nodes_pair_goal;
	std::map<Node*, int> node_depth_pair_start, node_depth_pair_goal;
	std::queue<Node*> startUnderConsideration, goalUnderConsideration;
	std::map<Node*, Node*> startPath, goalPath;
	std::stack<Node*> result;
	Node* startCurrent = nullptr;
	Node* goalCurrent = nullptr;

	startUnderConsideration.push(startPos);
	goalUnderConsideration.push(goalPos);

	startMemory.insert(startPos);
	goalMemory.insert(goalPos);

	node_depth_pair_start[startPos] = 0;
	node_depth_pair_goal[goalPos] = 0;

	depth_nodes_pair_start[node_depth_pair_start[startPos]].insert(startPos);
	depth_nodes_pair_goal[node_depth_pair_goal[goalPos]].insert(goalPos);

	bool foundValue = false;
	Node* commonNode = nullptr;
	int startCurrentDepth = 0;
	int startPrevDepth = 0;
	int goalCurrentDepth = 0;
	int goalPrevDepth = 0;

	
	while (!startUnderConsideration.empty() && !goalUnderConsideration.empty())
	{
		startCurrent = startUnderConsideration.front();
		goalCurrent = goalUnderConsideration.front();
		startUnderConsideration.pop();
		goalUnderConsideration.pop();
		
		if (foundValue)
			break;
		
		for (size_t i = 0; i < 4; i++)
		{
			if (startCurrent->hasNeighbour(i) && !startMemory.count(startCurrent->getNeighbour(i)))
			{
				startPath[startCurrent->getNeighbour(i)] = startCurrent;
				startUnderConsideration.push(startCurrent->getNeighbour(i));
				startMemory.insert(startCurrent->getNeighbour(i));
				node_depth_pair_start[startCurrent->getNeighbour(i)] = node_depth_pair_start[startCurrent] + 1;
				depth_nodes_pair_start[node_depth_pair_start[startCurrent->getNeighbour(i)]].insert(startCurrent->getNeighbour(i));

			}

			if (goalCurrent->hasNeighbour(i) && !goalMemory.count(goalCurrent->getNeighbour(i)))
			{
				goalPath[goalCurrent->getNeighbour(i)] = goalCurrent;
				goalUnderConsideration.push(goalCurrent->getNeighbour(i));
				goalMemory.insert(goalCurrent->getNeighbour(i));
				node_depth_pair_goal[goalCurrent->getNeighbour(i)] = node_depth_pair_goal[goalCurrent] + 1;
				depth_nodes_pair_goal[node_depth_pair_goal[goalCurrent->getNeighbour(i)]].insert(goalCurrent->getNeighbour(i));
				
			}
		}
		
		startCurrentDepth = node_depth_pair_start[startCurrent];
		goalCurrentDepth = node_depth_pair_goal[goalCurrent];
		if (startPrevDepth != startCurrentDepth && goalPrevDepth != goalCurrentDepth)
		{
			for (auto node : depth_nodes_pair_start[startCurrentDepth])
			{
				if (depth_nodes_pair_goal[goalCurrentDepth].count(node))
				{
					foundValue = true;
					commonNode = node;
					break;
				}
				if (depth_nodes_pair_goal[goalCurrentDepth -1].count(node))
				{
					foundValue = true;
					commonNode = node;
					break;
				}
			}
			startPrevDepth = startCurrentDepth;
			goalPrevDepth = goalCurrentDepth;
		}


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


	return result;
}
