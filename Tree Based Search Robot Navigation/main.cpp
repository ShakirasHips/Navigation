#include <iostream>
#include <algorithm>
#include <chrono>
#include "Map.h"
#include "Node.h"
#include "Solve.h"
#include "bitmap\bitmap_image.hpp"
#include "AuxiliaryFunctions.h"
#include <filesystem>
#include <experimental\filesystem>
#define log(x) std::cout << x << std::endl
#define filepath "C:/Users/Jayden/Desktop/Portfolio Projects/Tree Based Search Robot Navigation/Tree Based Search Robot Navigation/maps/test.txt"
#define filepath2 "C:/Users/Jayden/Desktop/ii.bmp"

int main(int argc, char** argv)
{
	if (!(argc == 3 || argc == 4))
	{
		std::cout << "Invailed argurments" << std::endl;
		return 0;
	}

	//Begin clock to check load times
	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	Map map;
	std::string searchAlg(argv[2]);
	std::cout << "Loading map...  ";

	if (!map.loadMap(argv[1])) 
	{
		std::cout << "Invailed file/filepath" << std::endl;
		return 0;
	}
	
	map.GenerateNodes();
	elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << elapsed.count() << " seconds" << std::endl;

	//Checks the file being loaded parent path so it can always output the bitmap to the same directory as the input bitmap
	std::string path(std::experimental::filesystem::absolute(argv[1]).parent_path().string());
	std::string fileName(std::experimental::filesystem::path(argv[1]).filename().string());
	path.append("\\");
	path.append(std::string(fileName).substr(0, std::string(fileName).size() - 4));


	std::string settings = "default";
	if (argc == 4)
	{
		settings = argv[3];
	}

	Solve solver(map.getStartingNode(), map.getEndingNode());
	//input args to lower case, 
	std::transform(searchAlg.begin(), searchAlg.end(), searchAlg.begin(), ::tolower);
	std::transform(settings.begin(), settings.end(), settings.begin(), ::tolower);

	std::stack<Node*> result;

	//Begin clock to check solving times
	std::cout << "Solving....  ";
	start = std::chrono::high_resolution_clock::now();


	if (searchAlg == "bfs")
	{
		result = solver.breadthFirstSearch();
		path.append("_BreadthFirstSearch_Answer");
	}
	else if (searchAlg == "dfs")
	{
		result = solver.depthFirstSearch();
		path.append("_DepthFirstSearch_Answer");
	}
	else if (searchAlg == "a*") 
	{
		result = solver.AStar();
		path.append("_AStar_Answer");
	}
	else if (searchAlg == "gbfs") 
	{
		result = solver.greedyBestFirstSearch();
		path.append("_GreedyBestFirstSearch_Answer");
	}
	else if (searchAlg == "bds") 
	{
		result = solver.bidirectionalSearch();
		path.append("_BidirectionalSearch_Answer");
	}
	else if (searchAlg == "ida*")
	{
		result = solver.iterativeDeepeningAStar();
		path.append("_IterativeDeepeningAStar_Answer");
	}
	else 
	{
		std::cout << "Invailed search argument" << std::endl;
		return 0;
	}

	//Ouputs collected data and time it took to solve
	elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << elapsed.count() << " seconds" << std::endl;
	std::cout << "Path length: " << result.size() << std::endl;
	std::cout << "Size of tree: " << solver.getSizeOfTree() << std::endl;

	//Checks file type and settings so it knows how to output the result
	if (fileName.substr(fileName.size() - 3) == "bmp")
	{
		if (settings == "default")
			aux::drawPath(result, argv[1], path.append(".bmp"));
		else if (settings == "debug")
		{
			std::vector<Node*> temp = solver.getNodesVisted();
			aux::drawPathWithVistedNodes(result, temp, argv[1], path.append("_debug.bmp"));
		}
	}
	else if (fileName.substr(fileName.size() - 3) == "txt")
	{
		aux::drawPath(result);
	}
		

	std::cout << "Done! :)" << std::endl;

	return 0;
}