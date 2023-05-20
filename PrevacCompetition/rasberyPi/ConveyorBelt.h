#pragma once
#pragma once
#include "Piece.h"
#include "control.h"
class Belt
{
public:

	Belt(Item::Piece*,int);
	~Belt();

	int quanity;
	Item::Piece* piece;

	double roomTemperature;
	int FurnaceTemperature;
	int thirdTemperature;
	double inFurnaceTime;


	void sendToFurnace();
	void sendToPress();
	void sendToSorter();
	void startHeat();
	void startHeat(int power);
	double nextTick();
private:
	int maxNoOfPieces();
	void setUpThings();
	void getTemps();
	int timer = 0;
	const double plateRadius = 0.5;
	const double plateWidth = 0.5;
	const int noOfPlates=5;
	const double furnaceSize = 2;
	const int furnacePower = 2000;
	const double efficiency = 0.8; // same shit as furnace time
	const double airSpecificHeat = 1020;
};