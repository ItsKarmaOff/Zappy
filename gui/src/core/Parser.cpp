/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Parser class implementation
*/
/**
 * @file Parser.cpp
 * @brief The Parser class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Parser.hpp"

namespace Gui
{
    Parser::Parser(int const &argc, char ** const &argv) : _argc(argc), _argv(argv)
    {
        _options = {
            {"h", "hostname", "\tmachine", "\tThe hostname of the server", HOSTNAME_OPTION, &Parser::_optionHostname},
            {"p", "port", "\tport", "\tThe port of the server", PORT_OPTION, &Parser::_optionPort},
            {"H", "help", "\t", "\tDisplay this help message", META_OPTION, &Parser::_optionHelp},
            {"V", "version", "\t", "\tDisplay the version of the program", META_OPTION, &Parser::_optionVersion},
            {"A", "authors", "\t", "\tDisplay the authors of the project", META_OPTION, &Parser::_optionAuthors},
        };
        std::string arg = "";
        bool found = false;

        DEBUG << "Parsing command line arguments";
        for (size_t index = 1; index < static_cast<size_t>(_argc); index++) {
            arg = _argv[index];
            found = false;
            for (const auto &option : _options) {
                if (arg == "-" + option.shortName || arg == "--" + option.longName) {
                    (this->*(option.function))(index);
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw Lib::Exceptions::Critical("Invalid option: \"" + arg + "\""
                    "\nPlease use -H or --help to see the list of available options.\"");
            }
        }
        for (const auto &option : _options) {
            if (option.type != NOT_REQUIRED && option.type != META_OPTION
            && (_optionsFound & option.type) == 0) {
                throw Lib::Exceptions::Critical("Missing option: -"
                    + option.shortName + " or --" + option.longName);
            }
        }
    }

    Parser::~Parser()
    {
        DEBUG << "Destroying Parser";
    }

    const std::string &Parser::getHostname() const
    {
        return _hostname;
    }

    const int &Parser::getPort() const
    {
        return _port;
    }

    void Parser::_optionHostname(size_t &index)
    {
        if (index + 1 >= static_cast<size_t>(_argc)) {
            throw Lib::Exceptions::Critical("Missing argument for -h (or --hostname) option");
        }
        _hostname = _argv[++index];
        if (_hostname.empty() || std::count(_hostname.begin(), _hostname.end(), '.') != 3) {
            throw Lib::Exceptions::Critical("Invalid argument for -h (or --hostname) option, it should be a valid hostname or IP address");
        }
        _optionsFound |= HOSTNAME_OPTION;
    }

    void Parser::_optionPort(size_t &index)
    {
        if (index + 1 >= static_cast<size_t>(_argc)) {
            throw Lib::Exceptions::Critical("Missing argument for -p or --port option");
        }
        try {
            _port = std::stoi(_argv[++index]);
        } catch (const std::invalid_argument &) {
            throw Lib::Exceptions::Critical("Invalid argument for -p (or --port) option, it must be a number between 0 and " + std::to_string(MAX_PORT_NUMBER));
        }
        if (_port < 0 || _port > MAX_PORT_NUMBER) {
            throw Lib::Exceptions::Critical("Invalid argument for -p (or --port) option, it must be a number between 0 and " + std::to_string(MAX_PORT_NUMBER));
        }
        _optionsFound |= PORT_OPTION;
    }

    void Parser::_optionHelp(size_t &)
    {
        std::cout << BOLD "USAGE:" RESET << std::endl
            << "\t" << _argv[0] << " -h hostname -p port" << std::endl << std::endl
            << BOLD "OPTIONS:" RESET << std::endl;
        for (const auto &option : _options) {
            if (option.type != META_OPTION) {
                std::cout << "\t-" << option.shortName << ", --" << option.longName
                    << "\t" << option.argument << "\t\t" << option.description << std::endl;
            }
        }
        std::cout << std::endl << BOLD "META-OPTIONS:" RESET << std::endl;
        for (const auto &option : _options) {
            if (option.type == META_OPTION) {
                std::cout << "\t-" << option.shortName << ", --" << option.longName
                    << "\t" << option.argument << "\t\t" << option.description << std::endl;
            }
        }
        throw Lib::Exceptions::Success("");
    }

    void Parser::_optionVersion(size_t &)
    {
        std::cout << BOLD "VERSION:" RESET << std::endl
            << "\tZappy GUI version 1.0.0" << std::endl
            << "\tBuilt on: " __DATE__ " at " __TIME__ << std::endl;
        throw Lib::Exceptions::Success("");
    }

    void Parser::_optionAuthors(size_t &)
    {
        std::cout << BOLD "AUTHORS:" RESET << std::endl
            << ITALIC "\t- Students of EPITECH Nice 2025 -" RESET << std::endl
            << "\tChristophe VANDEVOIR" << std::endl
            << "\tGianni TUERO" << std::endl
            << "\tLou PELLEGRINO" << std::endl
            << "\tNicolas TORO" << std::endl
            << "\tOlivier POUECH" << std::endl
            << "\tRaphaël LAUNAY" << std::endl;
        throw Lib::Exceptions::Success("");
    }
}
