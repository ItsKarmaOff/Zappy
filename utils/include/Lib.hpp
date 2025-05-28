/*
** EPITECH PROJECT, 2025
** Lib.hpp
** File description:
** Lib declaration
*/


#ifndef LIB_HPP
    #define LIB_HPP
    #include <string>
    #include <vector>
    #include <iostream>
    #include <chrono>
    #define UNUSED __attribute__((unused))

namespace Lib {
    /**
     * @brief Splits a string into a vector of strings based on a separator
     *
     * @param str The string to split
     * @param separator The separator to split the string with
     * @return std::vector<std::string> Vector containing the split string parts
     */
    std::vector<std::string> stringToVector(std::string str, std::string separator);

    /**
     * @brief Checks if a certain amount of time has passed since the last check
     *
     * @param ms_delay The delay in milliseconds to check against
     * @param lastTime Reference to the time point of the last check
     * @return bool True if the delay has passed, false otherwise
     */
    bool delay(int ms_delay, std::chrono::steady_clock::time_point &lastTime);
}


#endif // LIB_HPP
