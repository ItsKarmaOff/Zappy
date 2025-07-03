/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Parser class implementation
*/
/**
 * @file Parser.hpp
 * @brief Parser class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Lib.hpp"

/**
 * @class Parser
 * @brief Command line argument parser for Zappy AI client
 */
class Parser {
public:
    /**
     * @brief Constructor for Parser
     */
    Parser();
    
    /**
     * @brief Destructor for Parser
     */
    ~Parser();
    
    /**
     * @brief Parse command line arguments
     * @param argc Number of arguments
     * @param argv Array of argument strings
     */
    void parse(int argc, char **argv);
    
    /**
     * @brief Get the port number
     * @return The port number
     */
    int getPort() const { return _port; }
    
    /**
     * @brief Get the team name
     * @return The team name
     */
    const std::string &getName() const { return _name; }
    
    /**
     * @brief Get the machine hostname
     * @return The machine hostname
     */
    const std::string &getMachine() const { return _machine; }

protected:

private:
    int _port; ///< Server port number
    std::string _name; ///< Team name
    std::string _machine; ///< Server hostname or IP address
};

#endif /* !PARSER_HPP_ */