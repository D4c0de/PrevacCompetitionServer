#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
static struct StringOperation{
	
	static std::string IntToString(int*,int);
	static std::string IntToString(int*,int, int);
	static std::string IntToHexString(int*, int);
	static std::string IntToHexString(int*, int, int);
};

