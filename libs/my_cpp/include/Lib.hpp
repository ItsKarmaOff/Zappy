/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The Lib functions declaration
*/
/**
 * @file Lib.hpp
 * @brief The Lib functions declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
*/

#ifndef LIB_HPP_
    #define LIB_HPP_

    #include "Socket.hpp"

namespace Lib {
    /**
     * @brief Splits a string into a vector of strings based on a separator
     * @param str The string to split
     * @param separator The separator to split the string with
     * @return std::vector<std::string> Vector containing the split string parts
     */
    std::vector<std::string> stringToVector(std::string str, std::string separator);

    /**
     * @brief Checks if a certain amount of time has passed since the last check
     * @param ms_delay The delay in milliseconds to check against
     * @param lastTime Reference to the time point of the last check
     * @return bool True if the delay has passed, false otherwise
     */
    bool delay(int ms_delay, std::chrono::steady_clock::time_point &lastTime);

    /**
     * @brief Generates a random double between 0 and 1
     * @return double Random double between 0 and 1
     */
    inline double random_double();

    /**
     * @brief Generates a random double between min and max
     * @param min The minimum value
     * @param max The maximum value
     * @return double Random double between min and max
     */
    inline double random_double(double min, double max);

    /**
     * @brief Generates a random integer between min and max
     * @param min The minimum value
     * @param max The maximum value
     * @return int Random integer between min and max
     */
    inline int random_int(int min, int max);

    /**
     * @brief Converts a string to lowercase
     * @param str The string to convert
     * @return std::string The converted lowercase string
     */
    std::string toLower(const std::string& str);
}

#endif /* LIB_HPP_ */
