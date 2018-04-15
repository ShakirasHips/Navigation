#include "AuxiliaryFunctions.h"
#include <iostream>
#include "bitmap\bitmap_image.hpp"

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

void aux::drawPath(std::stack<Node*> s, std::string img_filepath, std::string dest_filepath)
{
	bitmap_image map(img_filepath);
	bitmap_image path = map;


	if (!map)
		return;
	s.pop();
	int redValue = 0;
	for(;;)
	{
		Node *temp = s.top();
		s.pop();
		if (s.empty())
			break;

		path.set_pixel(temp->getPosition().x, temp->getPosition().y, make_colour(0, 0, 255));
		
		if (redValue != 255)
			redValue++;
	}

	path.save_image(dest_filepath);
}
