#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include "Piece.h"
#include "Token.h"
class FileOperation
{
public:
	FileOperation();
	~FileOperation();
	sqlite3* db;
	int Insert(std::string, double, int, int, int);
	int getSize();
	/// <summary>
	/// Function Try to verify an account -1 if error
	/// </summary>
	/// <param name="login"></param>
	/// <param name="password"></param>
	int Auth(std::string, std::string);
	uint16_t* getTokenID(int);
	int getTokenUserId(int);
	int getTokenPermit(int);
	std::vector<Token> tokens;
	std::vector<Item::Piece>* getPiece();
	Item::Piece* getPiece(int ID);



private:
	char* ErrMsg;
	int rc;
	void Initialize();
};