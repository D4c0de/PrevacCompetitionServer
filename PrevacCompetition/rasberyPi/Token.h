#pragma once
#include <cstdint>
#include <chrono>

class Token
{
public:
	uint16_t tokenID[6];
	std::chrono::duration <int> Duration;
	std::chrono::system_clock::time_point Start;
	Token() {
		Start = std::chrono::system_clock::now();
	}
	Token(uint16_t* token) {
		Start = std::chrono::system_clock::now();
		Duration = std::chrono::minutes(BaseTime);
		CloneToken(token);

	}
	Token(uint16_t* token,int time ) {
		Start = std::chrono::system_clock::now();
		Duration = std::chrono::minutes(time);
		CloneToken(token);

	}

private:
	void CloneToken(uint16_t* token) {
		for (int i = 0; i < 6; i++)
		{
			tokenID[i] = token[i];
		}
	}
	const int BaseTime = 20;//base time is 20
};