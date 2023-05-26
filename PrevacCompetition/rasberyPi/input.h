#pragma once

#include "FileOperation.h"
#include "Conversion.h"
namespace input
{
	int* input(Conn* modbus,FileOperation* database) {


		int* reg;
		while (true)
		{
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
				std::string name =StringOperation::IntToString(reg,1);

				for (int i = 1; i < 10; i++)
				{
					if (reg[i] == 0) {
						break;
					}
					name.push_back(reg[i]);
				}
				Conn::reg_clear(modbus, 0);
				reg = Conn::reg_read_ten(modbus, 1);

				double heat = reg[0];
				int mass{ reg[1] }, temp{ reg[2] }, radius{ reg[3] };

				Conn::reg_clear(modbus, 1);
				Conn::reg_write_Second(modbus,database->Insert(name, heat, mass, temp, radius));
				Conn::reg_write(modbus, 0, 11);
				std::cout << "Added new type " << name << "\n";
			}

			else if (reg[0] == 3) //send all types to slave
			{
				
				Conn::reg_clear(modbus, 0);
				int size = database->getSize();
				if (size > 0)
				{
					Conn::reg_write(modbus, 1, size);

					std::vector<Item::Piece>* temp = database->getPiece();
					for (int i = 0; i < temp->size(); i++)
					{

						Conn::reg_write(modbus, i + 1, (*temp)[i].ID, (*temp)[i].color);
					}
					delete temp;

				}
				else
				{
					Conn::reg_write(modbus, 1, 9999);
				}
				std::cout << "Sended data to slave\n";
				
			}

			else if (reg[0] == 4) //auth
			{

				int loginSize = Conn::reg_read_single(modbus, 1);
				int passwordSize = Conn::reg_read_single(modbus, 2);
				std::string loginS = StringOperation::IntToString(Conn::reg_read_multiple(modbus, 3, loginSize),loginSize);
				std::string passwordS = StringOperation::IntToHexString(Conn::reg_read_multiple(modbus, 3 + loginSize, passwordSize),passwordSize);
				for (size_t i = 0; i * 10 < 4 + loginSize + passwordSize; i++)
				{
					Conn::reg_clear(modbus, i);
				}
				int test=database->Auth(loginS, passwordS);
				if (test==-1)
				{

				}
				else
				{

				}
			}
			delete[] reg;
		}
		
	}
}