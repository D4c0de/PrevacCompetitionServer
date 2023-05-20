#include "ConveyorBelt.h"
#include <math.h>
#include "RSP.h"


Belt::Belt(Item::Piece* piece, int amount)
{
	this->piece =piece;
	this->quanity = amount;
	setUpThings();
}

double Belt::nextTick()
{
	double t = timer;
	double in = inFurnaceTime;
	if (inFurnaceTime < 0)
	{
		return -1;
	}
	double ret = (t / in);
	timer++;
	if (ret > 0.98) {
		return -1;
	}
	return ret;

}

void Belt::setUpThings()
{
	std::vector<double>* temper = RSP::readTemperatureData();
	roomTemperature = (*temper)[0];
	FurnaceTemperature = (*temper)[1];
	thirdTemperature = (*temper)[2];


	if (maxNoOfPieces() < quanity) {
		return;//Too Many Pieces
	};

	double tempDiff{ piece->targetTemperature - roomTemperature };
	if (tempDiff < 0) {
		return;//Furnace is hotter then need
	}
	else
	{
		double airMass = (furnaceSize - piece->GetSize() * quanity);
		if (airMass < 0)
		{
			return;//"this error shuldend be in real sim"
		}
		double energyInFurnace{ (airMass * (FurnaceTemperature + 1) * airSpecificHeat) };

		double energyForPieces{ piece->mass * piece->specificHeat * tempDiff * quanity };
		double energyForAir{ airMass * airSpecificHeat * tempDiff };

		inFurnaceTime = (energyForAir + energyForPieces - energyInFurnace) / (furnacePower * efficiency);
		if (inFurnaceTime < 0)
		{
			return;//"Error"
		}
	}

}
int Belt::maxNoOfPieces()
{
	double przekatna = 2 * piece->radius;

	int maxPerPlate = floor(plateWidth / przekatna) * floor(plateWidth / przekatna);

	return maxPerPlate * noOfPlates;
}
Belt::~Belt()
{

}

void Belt::sendToFurnace()
{
	control::rspControll::SendFromWerhouse();
}

void Belt::sendToPress()
{
	control::rspControll::setFurnacePower(0);
	for (int i = 0; i < quanity; i++)
	{
		control::rspControll::sendToPress();
	}
}

void Belt::sendToSorter()
{
	control::rspControll::sendToSorter();
}

void Belt::startHeat()
{
	control::rspControll::setFurnacePower(100);
	//turn of furnace on max heatpower
}
void Belt::startHeat(int power) {
	control::rspControll::setFurnacePower(power);
	//set % of heatpower
}






