#pragma once
#include <cstdint>
#include <chrono>
#include <cstdint>
#include <random>
class Token
{
public:
	uint16_t tokenID[6];
	std::chrono::duration <int> Duration;
	std::chrono::system_clock::time_point Start;
	int userID;
	int tier;
	Token(int ID,int t) {
		Start = std::chrono::system_clock::now();
		Duration = std::chrono::minutes(BaseTime);
		SetToken();
		userID = ID;
		tier = t;
	}
	Token(int ID, int t,int time) {
		Start = std::chrono::system_clock::now();
		Duration = std::chrono::minutes(time);
		SetToken();
		userID = ID;
		tier = t;
	}

private:
	void SetToken() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<uint16_t> dis(0, 65535);
		for (int i = 0; i < 6; i++)
		{
			tokenID[i] = dis(gen);
		}
	}
	const int BaseTime = 20;//base time is 20min
};