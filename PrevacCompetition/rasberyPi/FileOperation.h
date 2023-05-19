#pragma once
#include <fstream>
#include <string>

#include "Piece.h"
struct FileOperation
{
	static void WriteToFile(std::string, float, int, int, int);
	static void ReadFromFile(std::vector<Item::Piece>* pieces);
};