#pragma once
#include "Piece.h"
class Belt
{
public:

	Belt(Item::Piece*,int);
	~Belt();

	int quanity;
	Item::Piece* piece;

	float roomTemperature;
	int FurnaceTemperature;
	int thirdTemperature;
	float inFurnaceTime;

	void startHeat();
	void startHeat(float power);
	float nextTick();

private:
	int maxNoOfPieces();
	void setUpThings();
	void getTemps();
	int timer = 0;
	const float plateRadius = 0.5;
	const float plateWidth = 0.5;
	const int noOfPlates=5;
	const float furnaceSize = 2;
	const int furnacePower = 2000;
	const float efficiency = 0.8; // same shit as furnace time
	const float airSpecificHeat = 1020;
};