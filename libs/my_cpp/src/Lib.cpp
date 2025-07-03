/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The Lib functions implementation
*/
/**
 * @file Lib.cpp
 * @brief The Lib functions implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Lib.hpp"

namespace Lib {
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

    double random_double()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    double random_double(double min, double max)
    {
        return min + (max - min) * random_double();
    }

    int random_int(int min, int max)
    {
        return int(random_double(min, max+1));
    }

    std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
            [](unsigned char c) { return std::tolower(c); });
        return result;
    }
}
