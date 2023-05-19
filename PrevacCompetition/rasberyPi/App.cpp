
#include "App.h"
#include "input.h"
#include <thread>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


MainApp::App::App(){

	modbus = new Conn();
	this->pieces = new Item::Pieces();
	SetUpThings();
}

MainApp::App::~App()
{
	delete modbus;
	delete pieces;
}

void MainApp::App::SetUpThings()
{
	this->pieces->load();
}

bool MainApp::App::run() {

	int* in = input::input(modbus, pieces);
	try
	{
		Belt belt = Belt(pieces->get(0[in]), 1[in]);// ARGS: piece, amount
		delete[] in;
		belt.startHeat(); // tak dla beki

		float loading = belt.nextTick();

		int last = (int)(loading * 100);
		do {
			if (last != (int)(loading * 100))
			{
				last = (int)(loading * 100);
				Conn::reg_write_Second(modbus, loading * 100);
			}
			input::s(time);
			loading = belt.nextTick();

		} while (loading >= 0);
		belt.startHeat(0.1);
		for (int i = 0; i < 30; i++)
		{
			input::s(time);
		}
		Conn::reg_write_Second(modbus, 100);
		std::cout << "task succesfull\n";

	}
	catch (const std::exception&)
	{
		
			Conn::reg_write_Second(modbus, 404);
			std::cout << "task faild\n";

	}
	return true;
}
