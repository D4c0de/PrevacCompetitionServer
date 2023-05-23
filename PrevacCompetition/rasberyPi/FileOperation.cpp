#include "FileOperation.h"
#include <string>
#include <sstream>
#include <vector>
int callback_piece(void* data, int argc, char** argv, char** azColName) {
	
	Item::Piece** piece=static_cast<Item::Piece**>(data);
	*piece = new Item::Piece(std::stoi(argv[0]), argv[1], std::stod(argv[2]), std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));
	return 0;
}
int callback_pieces(void* data, int argc, char** argv, char** azColName) {

	std::vector<Item::Piece>** pieces = static_cast<std::vector<Item::Piece>**>(data);
	for (int i = 0; i < argc; i += 6) {
		(*pieces)->push_back(Item::Piece(
			std::stoi(argv[i]),
			argv[i + 1],
			std::stod(argv[i + 2]),
			std::stod(argv[i + 3]),
			std::stod(argv[i + 4]),
			std::stod(argv[i + 5])
		));
	}
	return 0;
}
int callback_size(void* data, int argc, char** argv, char** azColName) {

	int* i = static_cast<int*>(data);
	*i = std::stoi(argv[0]);
	return 0;
}
int zero(void* NotUsed, int argc, char** argv, char** azColName) {
	return 0;
}

int insertId(void* data, int argc, char** argv, char** azColName) {
	int* id = static_cast<int*>(data);
	for (int i = 0; i < argc; i ++) {
		*id = argc + 1;
	}
	return 0;
}

FileOperation::FileOperation()
{
	ErrMsg = nullptr;
	rc = sqlite3_open("pieces.db", &db);
	if (rc!=SQLITE_OK)
	{
		std::cout << "can't open database";
	}
	else
	{
		createTable();
	}

}

FileOperation::~FileOperation()
{
	sqlite3_close(db);
}



int FileOperation::Insert(std::string name, double specificHeat, int mass, int temp, int radius)
{
	int id=getSize()+1;
	std::stringstream query{};
	query << "INSERT INTO Pieces(ID,Color, Radius, Mass, SpecificHeat, TargetTemperatre) "
		  << "VALUES("<< id <<", '" << name << "', "<< ((double)radius / 100)<<", " <<(double)mass/1000<<", "<< specificHeat <<", " << (temp/10)<<"); ";
	rc = sqlite3_exec(db, query.str().c_str(), zero, &id, &ErrMsg);

	if (rc!=SQLITE_OK)
	{
		std::cout << "problem with inserting";
		sqlite3_free(ErrMsg);
		return 404;
	}
	sqlite3_free(ErrMsg);

	return id;

}
int FileOperation::getSize()
{
	int size;
	std::stringstream query{};
	query << "SELECT count(ID) from Pieces;";
	rc = sqlite3_exec(db, query.str().c_str(), callback_size, &size, &ErrMsg);
	sqlite3_free(ErrMsg);
	return size;
}
Item::Piece* FileOperation::getPiece(int ID)
{
	Item::Piece* piece;
	std::stringstream query{};
	query << "SELECT * from Pieces WHERE ID =" <<ID <<";";
	rc = sqlite3_exec(db, query.str().c_str(), callback_piece,&piece, &ErrMsg);
	sqlite3_free(ErrMsg);
	return piece;
}
std::vector<Item::Piece>* FileOperation::getPiece()
{
	std::vector<Item::Piece>* pieces=new std::vector<Item::Piece>;
	std::stringstream query{};
	query << "SELECT * from Pieces ;";
	rc = sqlite3_exec(db, query.str().c_str(), callback_pieces, &pieces, &ErrMsg);
	sqlite3_free(ErrMsg);
	return pieces;
}
void FileOperation::createTable() //function create table if isnt exist
{
	std::string query = "CREATE TABLE 'Pieces' ('ID' INTEGER NOT NULL,'Color'TEXT,'Radius'REAL,'Mass'REAL,'SpecificHeat' INTEGER,'TargetTemperatre'	INTEGER,PRIMARY KEY('ID' AUTOINCREMENT)	)";
	rc = sqlite3_exec(db, query.c_str(), zero, 0, &ErrMsg);
	sqlite3_free(ErrMsg);
}
