/*
** EPITECH PROJECT, 2025
** Core.cpp
** File description:
** Core implementation
*/

#include "Core.hpp"
#include "Logs.hpp"
#include <cstring>

namespace gui
{
    Core::Core(int argc, char **argv)
        : _port(-1), _hostname("")
    {
        DEBUG << "Initializing Core";

        try {
            parseArguments(argc, argv);
        } catch (const std::exception &e) {
            ERROR << "EXCEPTION: " << e.what();
        }
    }

    void Core::parseArguments(int argc, char **argv)
    {
        DEBUG << "Parsing arguments";

        if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
            printUsage();
            return;
        } else if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--author") == 0) {
            std::cout << "Authors:" << std::endl;
            std::cout << "\tChristophe VANDEVOIR" << std::endl;
            std::cout << "\tGianni TUERO" << std::endl;
            std::cout << "\tLou PELLEGRINO" << std::endl;
            std::cout << "\tNicolas TORO" << std::endl;
            std::cout << "\tOlivier POUECH" << std::endl;
            std::cout << "\tRaphael LAUNAY" << std::endl;
            return;
        } else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
            std::cout << "Zappy GUI version 1.0" << std::endl;
            return;
        }

        if (argc < 5) {
            printUsage();
            throw std::invalid_argument("Not enough arguments provided");
        } else if (argc > 5) {
            printUsage();
            throw std::invalid_argument("Too many arguments provided");
        }

        for (int index = 1; index < argc; index++) {
            if (strcmp(argv[index], "-p") == 0) {
                if (index + 1 < argc) {
                    setPort(std::stoi(argv[index + 1]));
                    index++;
                } else {
                    throw std::invalid_argument("Missing port number after -p");
                }
            } else if (strcmp(argv[index], "-h") == 0) {
                if (index + 1 < argc) {
                    setHostname(argv[index + 1]);
                    index++;
                } else {
                    throw std::invalid_argument("Missing hostname after -h");
                }
            } else {
                throw std::invalid_argument("Unknown argument: " + std::string(argv[index]));
            }
        }

        if (_port == -1) {
            throw std::invalid_argument("Port number is required");
        }

        if (_hostname.empty()) {
            throw std::invalid_argument("Hostname is required");
        }
        DEBUG << "Parsed arguments: port= " << getPort() << ", hostname= " << getHostname();
    }

    void Core::printUsage() const
    {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        std::cout << "\noption\t\tdescription" << std::endl;
        std::cout << "-p port\t\tport number" << std::endl;
        std::cout << "-h machine\thostname of the server" << std::endl;
    }

    int Core::getPort() const
    {
        return _port;
    }

    const std::string &Core::getHostname() const
    {
        return _hostname;
    }

    void Core::setPort(int port)
    {
        if (port <= 0 || port > 65535)
            throw std::out_of_range("Port number must be between 1 and 65535");

        _port = port;
    }

    void Core::setHostname(const std::string &hostname)
    {
        if (hostname.empty())
            throw std::invalid_argument("Hostname cannot be empty");

        _hostname = hostname;
    }
}
