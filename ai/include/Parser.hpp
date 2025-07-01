/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Lib.hpp"

class Parser {
    public:
        Parser();
        ~Parser();
        void parse(int argc, char **argv);
        
        int getPort() const { return _port; }
        const std::string &getName() const { return _name; }
        const std::string &getMachine() const { return _machine; }

    protected:
    private:
        int _port;
        std::string _name;
        std::string _machine;
};

#endif /* !PARSER_HPP_ */