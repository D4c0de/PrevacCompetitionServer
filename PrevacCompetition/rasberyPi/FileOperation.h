#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include "Piece.h"
class FileOperation
{
public:
	FileOperation();
	~FileOperation();
	sqlite3* db;
	int Insert(std::string, double, int, int, int);
	int getSize();
	std::vector<Item::Piece>* getPiece();
	Item::Piece* getPiece(int ID);

private:
	char* ErrMsg;
	int rc;
	void createTable();
};