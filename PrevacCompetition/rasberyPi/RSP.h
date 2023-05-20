#pragma once

#include <vector>

namespace RSP {

#ifndef _WIN32
#include <string>
#include <dirent.h>
#include <string>
#include <iostream>
#include <fstream>
    std::vector<std::string> getSensorAddresses()
    {
        std::vector<std::string> sensorAddresses;


        std::string dataPath = "/sys/bus/w1/devices/";


        DIR* dir = opendir(dataPath.c_str());
        if (dir == nullptr)
        {
            std::cout << "Blod otwarcia katalogu: " << dataPath << std::endl;
            return sensorAddresses;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr)
        {
            std::string fileName = entry->d_name;

            if (fileName.substr(0, 2) == "28")
            {
                sensorAddresses.push_back(fileName);
            }
        }

        closedir(dir);

        return sensorAddresses;
    }

    std::vector<double>* readTemperatureData()
    {
        std::vector<std::string> sensorAddresses = getSensorAddresses();
        std::vector<double>* temperatureData = new std::vector<double>();

        for (const auto& address : sensorAddresses)
        {

            std::string filePath = "/sys/bus/w1/devices/" + address + "/temperature";

            std::ifstream file(filePath);
            if (!file)
            {
                std::cout << "Blod otwarcia pliku: " << filePath << std::endl;
                delete temperatureData;
                return nullptr;
            }


            std::string temperatureStr;
            std::getline(file, temperatureStr);


            double temperature = std::stod(temperatureStr) / 1000.0;
            temperatureData->push_back(temperature);


            file.close();
        }

        return temperatureData;
    }
#else
    std::vector<double>* readTemperatureData() {
        std::vector<double>* ret = new std::vector<double>;
        double roomTemperature = 20;
        double FurnaceTemperature = 20;
        double thirdTemperature = 20;
        ret->push_back(roomTemperature);
        ret->push_back(FurnaceTemperature);
        ret->push_back(thirdTemperature);
        return ret;
    }
#endif // !WIN_32
}
