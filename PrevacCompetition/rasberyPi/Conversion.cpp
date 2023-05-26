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
    std::string ret;
    std::vector<uint8_t> vec = IntToBytes(list, size, start);
    for (size_t i = 0; i < vec.size(); i++)
    {
        int low = vec[i] % 16;
        int high = (vec[i] - low) / 16;
        ret += dictionary(low);
        ret += dictionary(high);
    }
    delete[] list;
    return ret;
}

std::vector<uint8_t> StringOperation::IntToBytes(int* list, int size)
{

    return IntToBytes(list, size, 0);
}

std::vector<uint8_t> StringOperation::IntToBytes(int* list, int size, int start)
{
    
    std::vector<uint8_t> vec;
    for (int i = start; i < size; i++) {
        vec.push_back(static_cast<uint8_t>(list[i] & 0xFF));
        vec.push_back(static_cast<uint8_t>((list[i] >> 8) & 0xFF));
    }
    return vec;
}

std::string StringOperation::dictionary(int in)
{
    std::stringstream s{};
    if (in<10)
    {
        s << in;
    }
    else if(in==10)
    {
        s << "a";
    }
    else if (in == 11)
    {
        s << "b";
    }
    else if (in == 12)
    {
        s << "c";
    }
    else if (in == 13)
    {
        s << "d";
    }
    else if (in == 14)
    {
        s << "e";
    }
    else if (in == 15)
    {
        s << "f";
    }
    return s.str();
}
