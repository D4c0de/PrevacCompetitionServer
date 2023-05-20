#pragma once

#include <string>
#include <vector>

namespace Item {

	struct Piece
	{
		Piece();
		Piece(int,std::string, double, double, double, double);
		~Piece();
		double GetSize();
		int ID;
		std::string color;
		double radius;
		double mass;
		double targetTemperature;
		double specificHeat;
		const double high=0.2;
	};

}