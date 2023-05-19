
#include "ConveyorBelt.h"
#include <fstream>
#include <math.h>


Belt::Belt(Item::Piece* input, int amount)
{
	this->piece = input;
	this->quanity = amount;
	setUpThings();
}

float Belt::nextTick()
{
	float t = this->timer;
	float in = this->inFurnaceTime;
	if (inFurnaceTime < 0)
	{
		return -1;
	}
	float ret = (t / in);
	this->timer++;
	if (ret > 0.98) {
		return -1;
	}
	return ret;

}


void Belt::startHeat()
{

	//turn of furnace on max heatpower
}
void Belt::startHeat(float power) {
	
	//set % of heatpower
}

void Belt::setUpThings()
{
	getTemps();

	if (maxNoOfPieces() < quanity) {
		return;//Too Many Pieces
	};

	float tempDiff{ piece->targetTemperature - roomTemperature };
	if (tempDiff < 0) {
		return;//Furnace is hotter then need
	}
	else
	{
		float airMass = (furnaceSize - piece->GetSize() * quanity);
		if (airMass < 0)
		{
			return;//"this error shuldend be in real sim"
		}
		float energyInFurnace{ (airMass * (FurnaceTemperature + 1) * airSpecificHeat) };

		float energyForPieces{ piece->mass * piece->specificHeat * tempDiff * quanity };
		float energyForAir{ airMass * airSpecificHeat * tempDiff };

		inFurnaceTime = (energyForAir + energyForPieces - energyInFurnace) / (furnacePower * efficiency);
		if (inFurnaceTime < 0)
		{
			return;//"Error"
		}
	}
	
}
int Belt::maxNoOfPieces()
{
	float przekatna= 2* piece->radius;

	int maxPerPlate = floor(przekatna / plateWidth)*floor(przekatna/plateWidth);

	return maxPerPlate*noOfPlates;
}
Belt::~Belt()
{
	
}









void Belt::getTemps() {
	// TODO pobieranie danych z 1wire
	/*
	#include <wiringPi.h>
	std::string thermometerAddresses[3] = {
	"28-000000000001",
	"28-000000000002",
	"28-000000000003"
	};
	// Inicjalizacja biblioteki WiringPi
	if (wiringPiSetup() == -1) {
		std::cerr << "B³¹d inicjalizacji WiringPi" << std::endl;
		return 1;
	}
	// Odczyt temperatury z termometrów
	for (int i = 0; i < 3; i++) {
		float temperature = readTemperature(thermometerAddresses[i]);
		if (temperature != -1.0f) {
			std::cout << "Termometr " << thermometerAddresses[i] << ": " << temperature << "°C" << std::endl;
		}
	}

	float readTemperature(const std::string& address) {
	std::string path = "/sys/bus/w1/devices/" + address + "/w1_slave";
	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		std::cerr << "Nie mo¿na otworzyæ pliku " << path << std::endl;
		return -1.0f;
	}

	char line[256];
	float temperature = -1.0f;
	while (fgets(line, radiusof(line), file) != NULL) {
		if (strstr(line, "t=") != NULL) {
			temperature = std::stof(line + strstr(line, "t=") + 2) / 1000.0f;
			break;
		}
	}

	fclose(file);
	return temperature;
}

	*/
	roomTemperature = 20;
	FurnaceTemperature = 20;
	thirdTemperature = 20;
}