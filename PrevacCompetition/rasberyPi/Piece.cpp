#include <vector>
#include <string>
#include "Piece.h"
#include "FileOperation.h"


Item::Piece::Piece()
{
	
}

Item::Piece::Piece(const std::string& bufor)
{
	int i = 0;
	std::string input;
	while (bufor[i] != *" ")
	{
		input += bufor[i];
		i++;
	}
	color = input;
	input.clear();
	i++;
	while (bufor[i] != *" ")
	{
		input += bufor[i];
		i++;
	}
	specificHeat = std::stof(input);
	i++;
	input.clear();
	while (bufor[i] != *" ")
	{
		input += bufor[i];
		i++;
	}
	mass = std::stoi(input);
	mass /= 1000;
	i++;
	input.clear();
	while (bufor[i] != *" ")
	{
		input += bufor[i];
		i++;
	}
	radius = std::stoi(input);
	radius /= 1000;
	i++;
	input.clear();
	while (bufor[i] != *" ")
	{
		input += bufor[i];
		i++;
		if (i == bufor.size())
		{
			break;
		}
	}
	targetTemperature = std::stoi(input);
}

Item::Piece::Piece(std::string name, float value, int mass, int temp, int radius)
{
	this->color = name;
	this->mass = mass;
	this->radius = radius;
	this->targetTemperature = temp;
	this->specificHeat = value;
}

Item::Piece::~Piece()
{
}

float Item::Piece::GetSize()
{
	float size;
	size = radius * radius * 3, 14;
	return size;
}


//pieces
Item::Pieces::Pieces()
{
}

Item::Pieces::~Pieces()
{
}

void Item::Pieces::add(Piece added)
{
	tab.push_back(added);
}

Item::Piece* Item::Pieces::get(int no)
{

	return &tab[no];
}

void Item::Pieces::load()
{
	FileOperation::ReadFromFile(&tab);

	return;
}
