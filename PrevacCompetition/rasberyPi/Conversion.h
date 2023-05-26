#pragma once
#include <string>
#include <vector>
#include <sstream>
static struct StringOperation{
	
	static std::string IntToString(int*,int);
	static std::string IntToString(int*,int, int);
	static std::string IntToHexString(int*, int);
	static std::string IntToHexString(int*, int, int);
	static std::vector<uint8_t> IntToBytes(int*, int);
	static std::vector<uint8_t> IntToBytes(int*, int, int);
	static std::string dictionary(int);
};

