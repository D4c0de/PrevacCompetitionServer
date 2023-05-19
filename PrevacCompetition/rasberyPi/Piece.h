#pragma once

#include <string>
#include <vector>

namespace Item {

	struct Piece
	{
		Piece();
		Piece(const std::string&);
		Piece(std::string, float, int, int, int);
		~Piece();
		float GetSize();
		std::string color;
		float radius;
		float mass;
		int targetTemperature;
		int specificHeat;
		const double high=0.2;
	};

	struct Pieces
	{
		Pieces();
		~Pieces();


		std::vector<Piece> tab;
		void add(Piece);
		Piece* get(int);
		void load();
	};

}