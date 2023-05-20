#include "App.h"
#include "input.h"
#include <chrono>

MainApp::App::App() {

	modbus = new Conn();
	DataBase = new FileOperation();
}

MainApp::App::~App()
{
	delete modbus;
	delete DataBase;
}

bool MainApp::App::run() {

	int* in = input::input(modbus, DataBase);
	Belt belt = Belt(DataBase->getPiece(0[in]), 1[in]);// ARGS: piece, amount
	delete[] in;
	Conn::reg_write(modbus, 0, 11);
	Conn::readRC(modbus);
	belt.sendToFurnace();
	Conn::reg_write(modbus, 0, 12);
	Conn::readRC(modbus);

	belt.startHeat();
	auto start2 = std::chrono::high_resolution_clock::now();
	double loading = belt.nextTick();
	int last = (int)(loading * 100);
	do {
		Conn::readRC(modbus);
		auto start = std::chrono::high_resolution_clock::now();
		if (last != (int)(loading * 100))
		{
			last = (int)(loading * 100);
			Conn::reg_write_Second(modbus, loading * 100);

		}
		auto end = std::chrono::high_resolution_clock::now();
		while (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < time) {}
		if (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start2).count() < 2)
		{
			start2 = std::chrono::high_resolution_clock::now();
		}
		loading = belt.nextTick();
	} while (loading >= 0);
	Conn::readRC(modbus);
	belt.startHeat(10);

	for (int i = 0; i < 10; i++) {
		for (int i = 0; i < 3; i++)
		{
			auto start = std::chrono::high_resolution_clock::now();
			while (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count() < time) {}
		}
		Conn::readRC(modbus);
	}
	Conn::reg_write_Second(modbus, 100);
	Conn::readRC(modbus);
	Conn::reg_write(modbus, 0, 13);
	Conn::readRC(modbus);
	belt.sendToPress();
	Conn::reg_write(modbus, 0, 14);
	Conn::readRC(modbus);
	belt.sendToSorter();
	Conn::reg_write(modbus, 0, 15);
	Conn::readRC(modbus);

	std::cout << "task succesfull\n";
	return true;
}
