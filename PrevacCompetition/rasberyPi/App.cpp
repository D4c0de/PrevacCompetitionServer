#include "App.h"
#include "input.h"
#include <chrono>

MainApp::App::App() {

	modbus = new Conn();
	DataBase = new FileOperation();

	belt = nullptr;


}

MainApp::App::~App()
{
	delete modbus;
	delete DataBase;

}

void MainApp::App::ServerStart(Conn* modbus)
{
	Conn::readRC(modbus);

}

bool MainApp::App::Run() {


	try
	{
		Begin();
		Heat();
		End();
	}
	catch (const std::string e1)
	{
		std::cout << "Error "<< e1;
		return false;
	}


	std::cout << "task succesfull\n";
	delete belt;
	return true;

}

void MainApp::App::Begin()
{
	int* in = input::input(modbus, DataBase);
	belt = new Belt(DataBase->getPiece(0[in]), 1[in]);// ARGS: piece, amount
	delete[] in;
	Conn::reg_write(modbus, 0, 11);
	belt->sendToFurnace();
}

void MainApp::App::Heat()
{
	Conn::reg_write(modbus, 0, 12);
	belt->startHeat();
	double loading = belt->nextTick();
	int last = (int)(loading * 100);
	do {
		auto start = std::chrono::high_resolution_clock::now();
		if (last != (int)(loading * 100))
		{
			last = (int)(loading * 100);
			Conn::reg_write_Second(modbus, loading * 100);

		}

		while (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < time) {}

		loading = belt->nextTick();
	} while (loading >= 0);
	belt->startHeat(10);
	Conn::reg_write(modbus, 0, 13);
	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < 3; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			while (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < time) {}
		}
	}
	Conn::reg_write_Second(modbus, 100);
}

void MainApp::App::End()
{
	
	Conn::reg_write(modbus, 0, 14);
	belt->sendToPress();
	Conn::reg_write(modbus, 0, 15);
	belt->sendToSorter();
	Conn::reg_write(modbus, 0, 16);

}
