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
#define filepath2 "C:/Users/Jayden/Desktop/jk.bmp"

int main(int argc, char** argv)
{
	//Map map;
	//map.loadMap(filepath);
	//map.GenerateNodes();
	//Solve solver(map.getStartingNode(), map.getEndingNode()); 
	////log(solver.breadthFirstSearch().size());
	//aux::drawPath(solver.depthFirstSearch());
	////aux::drawPath(solver.iterativeDeepeningAStar(), filepath2, "C:/Users/Jayden/Desktop/Ast.bmp" );
	//std::cin.get();
	
	if (argc != 3)
	{
		std::cout << "Invailed argurments" << std::endl;
		return 0;
	}

	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	Map map;
	std::string searchAlg(argv[2]);
	std::cout << "Loading map...  ";
	std::stack<Node*> result;
	if (!map.loadMap(argv[1])) 
	{
		std::cout << "Invailed file/filepath" << std::endl;
		return 0;
	}


	map.GenerateNodes();
	elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << elapsed.count() << " seconds" << std::endl;

	std::string path(std::experimental::filesystem::absolute(argv[1]).parent_path().string());
	std::string fileName(std::experimental::filesystem::path(argv[1]).filename().string());
	path.append("\\");
	path.append(std::string(fileName).substr(0, std::string(fileName).size() - 4));

	Solve solver(map.getStartingNode(), map.getEndingNode());
	std::transform(searchAlg.begin(), searchAlg.end(), searchAlg.begin(), ::tolower);

	std::cout << "Solving....  ";
	start = std::chrono::high_resolution_clock::now();

	if (searchAlg == "bfs")
	{
		result = solver.breadthFirstSearch();
		path.append("_BreadthFirstSearch_Answer.bmp");
	}
	else if (searchAlg == "dfs")
	{
		result = solver.depthFirstSearch();
		path.append("_DepthFirstSearch_Answer.bmp");
	}
	else if (searchAlg == "a*") 
	{
		result = solver.AStar();
		path.append("_AStar_Answer.bmp");
	}
	else if (searchAlg == "gbfs") 
	{
		result = solver.greedyBestFirstSearch();
		path.append("_GreedyBestFirstSearch_Answer.bmp");
	}
	else if (searchAlg == "bds") 
	{
		result = solver.bidirectionalSearch();
		path.append("_BidirectionalSearch_Answer.bmp");
	}
	else 
	{
		std::cout << "Invailed search argument" << std::endl;
		return 0;
	}
	elapsed = std::chrono::high_resolution_clock::now() - start;
	std::cout << elapsed.count() << " seconds" << std::endl;
	std::cout << "Path length: " << result.size() << std::endl;
	std::cout << "Size of tree: " << solver.getSizeOfTree() << std::endl;

	if (fileName.substr(fileName.size() - 3) == "bmp")
		aux::drawPath(result, argv[1], path);
	else if (fileName.substr(fileName.size() - 3) == "txt")
		aux::drawPath(result);

	std::cout << "Done! :)" << std::endl;

	return 0;
}