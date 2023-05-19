#pragma once

#include <iostream>
#include <vector>
#include "connect.h"
#include "ConveyorBelt.h"
#include "Piece.h"


namespace MainApp {

	class App
	{
	public:
		App();
		~App();
		
		Conn* modbus;
		Item::Pieces* pieces;
		void SetUpThings();
		bool run();
	private:
		const int time = 100;// Base 1000, less while debug
	};
}

