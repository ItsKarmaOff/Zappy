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
        throw Lib::Exceptions::Critical("USAGE: ./zappy_ai -p port -n name -h machine\n");
    }
    if (argc != 7) {
        throw Lib::Exceptions::Critical("Not enough arguments provided.");
    }
    
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (i + 1 >= argc) {
            throw Lib::Exceptions::Critical("Missing value for argument: " + arg);
        }
        
        if (arg == "-p") {
            _port = std::stoi(argv[i + 1]);
            if (_port <= 0 || _port > 65535) {
                throw Lib::Exceptions::Critical("Invalid port number. It must be between 1 and 65535.");
            }
        } else if (arg == "-n") {
            _name = argv[i + 1];
            if (_name.empty()) {
                throw Lib::Exceptions::Critical("Name cannot be empty.");
            }
        } else if (arg == "-h") {
            _machine = argv[i + 1];
            if (_machine.empty()) {
                throw Lib::Exceptions::Critical("Machine cannot be empty.");
            }
        } else {
            throw Lib::Exceptions::Critical("Unknown argument: " + arg);
        }
    }
    
    if (_port == 0) {
        throw Lib::Exceptions::Critical("Port not specified.");
    }
    if (_name.empty()) {
        throw Lib::Exceptions::Critical("Name not specified.");
    }
}
//}
