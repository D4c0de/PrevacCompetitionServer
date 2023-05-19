#include "FileOperation.h"
#include <fstream>
#include <string>
#include <vector>
void FileOperation::WriteToFile(std::string name, float value, int mass, int temp, int radius)
{

	std::string lain = name + " " + std::to_string(value) + " " + std::to_string(mass) + " " + std::to_string(radius) + " " + std::to_string(temp / 10);
	std::fstream file;
	file.open("PiecesDB.txt", std::ios::app);
	file << lain << "\n";
	file.close();

}

void FileOperation::ReadFromFile(std::vector<Item::Piece>* pieces)
{
	std::fstream file;
	file.open("PiecesDB.txt", std::ios::in);
	char bufor[255];
	while (file.getline(bufor, 255)) {
		pieces->push_back(Item::Piece(bufor));
	}

}
