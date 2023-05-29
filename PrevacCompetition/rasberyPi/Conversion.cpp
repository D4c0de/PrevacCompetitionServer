#include "Conversion.h"

std::string StringOperation::IntToString(int* list,int size)
{
    return IntToString(list,size,0);
}

std::string StringOperation::IntToString(int* list,int size,int start)
{
    std::string ret{};
    for (int i = start; i < size; i++) {
        if (list[i] < UINT8_MAX) {
            ret += static_cast<char>(list[i]);
        }
        else {
            ret += static_cast<char>(list[i] & 0xFF);
            ret += static_cast<char>((list[i] >> 8) & 0xFF);
        }
    }
    delete[] list;
    return ret;
}

std::string StringOperation::IntToHexString(int* list, int size)
{
    return IntToHexString(list,size,0);
}

std::string StringOperation::IntToHexString(int* list, int size, int start)
{
    std::ostringstream oss;
    for (int i = start; i < size; i++)
    {
        oss << std::hex << std::nouppercase << list[i];
    }
    delete[] list;

    return oss.str();
}