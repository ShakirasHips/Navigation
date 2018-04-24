#include "AuxiliaryFunctions.h"
#include <iostream>
#include "bitmap\bitmap_image.hpp"


//string parser splits strings by a char
//used to read lines in text file
std::vector<std::string>& aux::stringParser(std::string & s, char delim, std::vector<std::string>& elems)
{
	s.erase(0, 1);
	s.erase(s.size() - 1);
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;

}

//string parser but returns ints instead
//used to get data out of text files
std::vector<int>& aux::stringParser(std::string &s, char delim, std::vector<int> &elems)
{
	s.erase(0, 1);
	s.erase(s.size() - 1);
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(std::stoi(item));
	}
	return elems;

}

//prints stack used for testing
void aux::printStack(std::stack<Node*> s) 
{
	Node* temp;
	while (!s.empty())
	{
		temp = s.top();
		s.pop();
		std::cout << temp->getPosition().x << ", " << temp->getPosition().y << std::endl;
	}
}

//prints path to console
//assumption made that each node is 1 posisition away from each other this can be fixed
void aux::drawPath(std::stack<Node*> s) 
{
	Node* prev;
	Node* current;
	if (s.empty())
	{
		std::cout << "No path found!! :(" << std::endl;
		return;
	}
	prev = s.top();
	s.pop();
	while (!s.empty())
	{
		current = s.top();
		s.pop();
		
		if (current->getPosition().x - prev->getPosition().x == 1)
			std::cout << "Right" << std::endl;
		else if (current->getPosition().x - prev->getPosition().x == -1)
			std::cout << "Left" << std::endl;
		else if (current->getPosition().y - prev->getPosition().y == 1)
			std::cout << "Down" << std::endl;
		else if (current->getPosition().y - prev->getPosition().y == -1)
			std::cout << "Up" << std::endl;
		
		prev = current;
	}
}

//draw path on bitmap that is loaded, ouputs new file.
void aux::drawPath(std::stack<Node*> s, std::string img_filepath, std::string dest_filepath)
{
	bitmap_image map(img_filepath);
	bitmap_image path = map;
	
	if (!map)
		return;

	if (s.empty())
	{
		std::cout << "No path found!! :(" << std::endl;
		return;
	}
	s.pop();

	for(;;)
	{
		Node *temp = s.top();
		s.pop();
		if (s.empty())
			break;

		path.set_pixel(temp->getPosition().x, temp->getPosition().y, make_colour(0, 0, 255));
	}

	path.save_image(dest_filepath);
}

//draws path and draws where tree has expanded to
void aux::drawPathWithVistedNodes(std::stack<Node*> s, std::vector<Node*> v, std::string img_filepath, std::string dest_filepath)
{
	bitmap_image map(img_filepath);
	bitmap_image path = map;

	if (!map)
		return;
	for (auto node: v)
	{
		path.set_pixel(node->getPosition().x, node->getPosition().y, make_colour(0, 255, 255));
	}

	if (s.empty())
	{
		std::cout << "No path found!! :(" << std::endl;
		path.save_image(dest_filepath);
		return;
	}

	s.pop();
	for (;;)
	{
		Node *temp = s.top();
		s.pop();
		if (s.empty())
			break;

		path.set_pixel(temp->getPosition().x, temp->getPosition().y, make_colour(0, 0, 255));
	}

	path.save_image(dest_filepath);
}
