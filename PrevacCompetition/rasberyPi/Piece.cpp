#include <vector>
#include <string>
#include "Piece.h"


Item::Piece::Piece()
{
	ID = NULL;
	color = "";
	specificHeat = NULL;
	mass = NULL;
	targetTemperature = NULL;
	radius = NULL;
}

Item::Piece::Piece(int id,std::string name, double value, double mass, double temp, double radius)
{
	this->ID = id;
	this->color = name;
	this->specificHeat = value;
	this->mass = mass;
	this->targetTemperature = temp;
	this->radius = radius;
}

Item::Piece::~Piece()
{
}

double Item::Piece::GetSize()
{
	double size;
	size = radius * radius * 3.14;
	return size;
}