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

Item::Piece::Piece(int id,std::string name, double radius, double mass, double specificHeat, double targetTemperature)
{
	this->ID = id;
	this->color = name;
	this->specificHeat = specificHeat;
	this->mass = mass;
	this->targetTemperature = targetTemperature;
	this->radius = radius;
}

Item::Piece::~Piece()
{
}
/// <summary>
/// 
/// </summary>
/// <returns>Size of pieces m^2</returns>
double Item::Piece::GetSize()
{
	double size;
	size = radius * radius * 3.14;
	return size;
}