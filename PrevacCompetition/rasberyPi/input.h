#pragma once

#include "FileOperation.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


/*
#include <string>
#include <vector>
#include <iostream>
#include "Piece.h"
#include "connect.h"
*/
namespace input
{
	void s(int time) {  //using coz i like to debug on Windows :D
#ifdef _WIN32
		Sleep(time);
#else
		sleep(time / 1000);
#endif
	}

	int* input(Conn* modbus, Item::Pieces* pieces) {


		std::vector<int> reg;
		while (true)
		{
			modbus->readRC();
			reg = Conn::reg_read_ten(modbus, 0);
			if (reg[0] == 1) // run program
			{
				int* i = new int[2];
				std::cout << "New task added \n";
				i[0] = (Conn::reg_read_single(modbus, 1));
				i[1] = (Conn::reg_read_single(modbus, 2));
				Conn::reg_clear(modbus, 0);
				return i;
			}
			else if (reg[0] == 2)// add new type
			{
				std::string name;

				for (int i = 1; i < 10; i++)
				{
					if (reg[i] == 0) {
						break;
					}
					name.push_back(reg[i]);
				}
				Conn::reg_clear(modbus, 0);
				reg = Conn::reg_read_ten(modbus, 1);

				float heat = reg[0];
				int mass{ reg[1] }, temp{ reg[2] }, radius{ reg[3] };

				Conn::reg_clear(modbus, 1);
				FileOperation::WriteToFile(name, heat, mass, temp, radius);
				pieces->add(Item::Piece(name, heat, mass, temp, radius));
				std::cout << "Added new type " << name << "\n";
			}

			else if (reg[0] == 3) //send all types to slave
			{
				
				Conn::reg_clear(modbus, 0);
				if (pieces->tab.size() > 0)
				{
					Conn::reg_write(modbus, 1, pieces->tab.size());
					for (int i = 0; i < pieces->tab.size(); i++)
					{
						Conn::reg_write(modbus, i + 1, pieces->get(i)->color);
					}
				}
				else
				{
					Conn::reg_write(modbus, 1, 9999);
				}
				std::cout << "Sended data to slave\n";
				
			}
			else
			{
				//s(2000);
			}
		}

	};
}