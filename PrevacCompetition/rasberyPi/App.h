#pragma once

#include <iostream>
#include <vector>
#include "connect.h"
#include "ConveyorBelt.h"
#include "FileOperation.h"


namespace MainApp {

	class App
	{
	public:
		App();
		~App();
		Conn* modbus;
		FileOperation* DataBase;
		bool run();
	private:
		const int time = 100;// Base 1000, less while debug
	};
}

