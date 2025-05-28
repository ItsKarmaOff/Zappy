/*
** EPITECH PROJECT, 2025
** Lib.cpp
** File description:
** Lib in ~/Documents/EPITECH/TEK2/NWP/BNWP400_jetpack/src/utils
*/

#include "Lib.hpp"
namespace Lib
{
    std::vector<std::string> stringToVector(std::string str, std::string separator)
    {
        std::vector<std::string> array;
        size_t pos = str.find_first_not_of(separator, 0);
        while (pos != std::string::npos) {
            size_t i = str.find_first_of(separator, pos);
            if (i == std::string::npos)
                i = str.length();
            array.push_back(str.substr(pos, i - pos));
            pos = str.find_first_not_of(separator, i);
        }
        return array;
    }

    bool delay(int ms_delay, std::chrono::steady_clock::time_point &lastTime)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration<float>(now - lastTime);
        if (elapsed.count() > ms_delay / 1000.0f) {
            lastTime = now;
            return true;
        }
        return false;
    }
}