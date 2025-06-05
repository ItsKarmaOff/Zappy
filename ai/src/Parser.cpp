/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Parser
*/

#include "Parser.hpp"

Parser::Parser()
{
    _port = 0;
    _name = "";
    _machine = "localhost";
}

Parser::~Parser()
{
}

void Parser::parse(int argc, char **argv)
{
    if (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        throw Lib::Exceptions::Help("USAGE: ./zappy_ai -p port -n name -h machine\n");
    }
    if (argc != 7) {
        throw Lib::Exceptions::Critical("Not enough arguments provided.");
    }
    _port = argv[2] ? std::stoi(argv[2]) : 0;
    if (_port <= 0 || _port > 65535) {
        throw Lib::Exceptions::Critical("Invalid port number. It must be between 1 and 65535.");
    }
    _name = argv[4] ? argv[4] : "";
    if (_name.empty()) {
        throw Lib::Exceptions::Critical("Name cannot be empty.");
    }
    _machine = argv[6] ? argv[6] : "localhost";
    if (_machine.empty()) {
        throw Lib::Exceptions::Critical("Machine cannot be empty.");
    }
}

