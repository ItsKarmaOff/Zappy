/*
** EPITECH PROJECT, 2025
** Core.cpp
** File description:
** Core implementation
*/
/**
 * @file Core.cpp
 * @brief Core implementation for the GUI
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Core.hpp"
#include "Logs.hpp"
#include <mutex>

namespace Gui
{
    //////////////////////// Constructors and Destructor ///////////////////////

    Core::Core(int argc, char **argv)
        : _port(-1), _hostname(""), _graphics()
    {
        DEBUG << "Construct Core";

        _parseArguments(argc, argv);
        _initClient();
    }



    //////////////////////// Main Methods //////////////////////////////////////

    void Core::run()
    {
        DEBUG << "Running Core";

        isRunning = true;
        std::thread communicationThread(&Core::_communicationThread, this);
        _gameThread();

        communicationThread.join();
    }

    void Core::sendCommand(int fd, const std::vector<std::string> &command)
    {
        std::string commandStr;

        for (std::size_t index = 0; index < command.size(); index++) {
            if (index != 0)
                commandStr += " ";
            commandStr += command[index];
        }
        DEBUG << "Send command: " << commandStr;
        commandStr += "\n";
        if (dprintf(fd, "%s", commandStr.c_str()) < 0) {
            ERROR << "Server closed the connection.";
            isRunning = false;
        }
    }

    std::string Core::getResponse()
    {
        char tmp = 0;
        std::string response;
        int readSize = 0;

        readSize = read(_clientSocket->getSocket(), &tmp, 1);
        while (readSize > 0) {
            response += tmp;
            if (tmp == '\n')
                break;
            readSize = read(_clientSocket->getSocket(), &tmp, 1);
        }
        if (readSize == -1) {
            ERROR << "Server closed the connection.";
            isRunning = false;
        }
        while (!response.empty() && response.back() == '\n')
            response.pop_back();
        DEBUG << response;
        return response;
    }



    //////////////////////// Getters ///////////////////////////////////////////

    int Core::getPort() const
    {
        return _port;
    }

    const std::string &Core::getHostname() const
    {
        return _hostname;
    }



    //////////////////////// Setters ///////////////////////////////////////////

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



    //////////////////////// Utility Methods ///////////////////////////////////

    void Core::printUsage() const
    {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        std::cout << "\noption\t\tdescription" << std::endl;
        std::cout << "-p port\t\tport number" << std::endl;
        std::cout << "-h machine\thostname of the server" << std::endl;
    }



    //////////////////////// Private Methods ///////////////////////////////////

    void Core::_parseArguments(int argc, char **argv)
    {
        DEBUG << "Parsing arguments";

        if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
            printUsage();
            return;
        } else if (std::string(argv[1]) == "-a" || std::string(argv[1]) == "--author") {
            std::cout << "Authors:" << std::endl;
            std::cout << "\tChristophe VANDEVOIR" << std::endl;
            std::cout << "\tGianni TUERO" << std::endl;
            std::cout << "\tLou PELLEGRINO" << std::endl;
            std::cout << "\tNicolas TORO" << std::endl;
            std::cout << "\tOlivier POUECH" << std::endl;
            std::cout << "\tRaphael LAUNAY" << std::endl;
            return;
        } else if (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version") {
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
            if (std::string(argv[index]) == "-p") {
                if (index + 1 < argc) {
                    setPort(std::stoi(argv[index + 1]));
                    index++;
                } else {
                    throw std::invalid_argument("Missing port number after -p");
                }
            } else if (std::string(argv[index]) == "-h") {
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

    void Core::_initClient()
    {
        DEBUG << "Initializing Core";

        DEBUG << "Init client: IP: " << _hostname << " PORT: " << _port;
        _clientSocket = std::make_unique<Lib::Socket>(AF_INET, SOCK_STREAM, 0);

        _client.sin_family = AF_INET;
		_client.sin_addr.s_addr = inet_addr(_hostname.c_str());
		_client.sin_port = htons(_port);

        if (connect(_clientSocket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
			throw Lib::Exceptions::Critical("Connect failed: " + std::string(strerror(errno)));

        std::cout << DARK_GREY "Connecting to server..." RESET << std::endl;

        if (getResponse() != "WELCOME")
            throw Lib::Exceptions::Critical("Connection failed.");

        std::cout << BOLD "Connected to server (" << _hostname << ":" << _port << ")." RESET << std::endl;
    }

    void Core::_communicationThread()
    {
        std::string response;

        while (isRunning.load()) {
            std::unique_lock<std::mutex> lockCommandQueue(_commandsQueueMutex);
            if (!_commandsQueue.empty()) {
                std::vector<std::string> command = _commandsQueue.front();
                _commandsQueue.pop();
                sendCommand(_clientSocket->getSocket(), command);
                std::unique_lock<std::mutex> lockResponseQueue(_responseQueueMutex);
                _responseQueue.push(getResponse());
                lockResponseQueue.unlock();
            }
            lockCommandQueue.unlock();
        }
    }

    void Core::_gameThread()
    {
        _graphics.init();
        _graphics.run(isRunning);
    }
}
