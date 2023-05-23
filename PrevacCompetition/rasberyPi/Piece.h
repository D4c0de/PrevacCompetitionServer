#pragma once

#include <string>
#include <vector>

namespace Item {

	struct Piece
	{
		Piece();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="id"></param>
		/// <param name="name"></param>
		/// <param name="radius"></param>
		/// <param name="mass"></param>
		/// <param name="specificHeat"></param>
		/// <param name="TargetTemperature"></param>

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