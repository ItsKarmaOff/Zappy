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

namespace Gui
{
    //////////////////////// Constructors and Destructor ///////////////////////

    Core::Core(int argc, char **argv)
        : _port(-1), _hostname("")
    {
        DEBUG << "Construct Core";

        Parser parser(argc, argv);
        _hostname = parser.getHostname();
        _port = parser.getPort();

        _initClient();
        _queueManager = std::make_shared<QueueManager>();
        _answer = "";
    }



    //////////////////////// Main Methods //////////////////////////////////////

    void Core::run()
    {
        DEBUG << "Running Core";
        isRunning = true;

        std::thread communicationThread(&Core::_communicationThread, this);
        /* fonction qui permet d'envoyer des commandes dans le graphique */
        // std::thread debug(&Core::manual, this);
        _gameThread();

        communicationThread.join();
        // debug.join();
    }

    void Core::manual()
    {
        while (isRunning) {
            std::string buffer;
            if (!std::getline(std::cin, buffer)) {
                ERROR << "Can't getline";
                continue;
            }
            std::vector<std::string> cmd = Lib::stringToVector(buffer, " \t\n");
            _queueManager->pushCommand(cmd);
        }
    }

    void Core::sendCommand(int fd, const std::vector<std::string> &command)
    {
        std::string commandStr;

        for (std::size_t index = 0; index < command.size(); index++) {
            if (index != 0)
                commandStr += " ";
            commandStr += command[index];
        }
        DEBUG << "Send command: [" << commandStr << "]";
        if (dprintf(fd, "%s\n", commandStr.c_str()) < 0) {
            ERROR << "Server closed the connection.";
            isRunning = false;
        }
    }

    std::string Core::getResponse()
    {
        int nb = 0;
        std::string response;
        char tmp[1] = {0};
        while ((nb = read(_clientSocket->getSocket(), tmp, 1)) > 0) {
            response.append(tmp, nb);
            auto pos = response.find('\n');
            if (pos != std::string::npos) {
                response.erase(pos);
                break;
            }
        }
        if (nb == -1) {
            ERROR << "Server closed the connection.";
            isRunning = false;
        }
        while (!response.empty() && response.back() == '\n')
            response.pop_back();
        if (!response.empty())
            DEBUG << "Received: [" << response << "]";
        return response;
    }



    //////////////////////// Private Methods ///////////////////////////////////

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

        _pollFd = {_clientSocket->getSocket(), POLLIN, 0};
        std::cout << BOLD "Connected to server (" << _hostname << ":" << _port << ")." RESET << std::endl;
    }

    void Core::readIfResponse()
    {
        if (poll(&_pollFd, 1, 0) > 0 && (_pollFd.revents & POLLIN)) {
            _answer += getResponse();
            if (!_answer.empty()) {
                _queueManager->pushResponse(_answer);
                _answer = "";
            }
        }
    }
    void Core::sendIfCommand()
    {
        if (_queueManager->hasCommands()) {
            std::vector<std::string> command = _queueManager->popCommand();
            if (!command.empty())
                sendCommand(_clientSocket->getSocket(), command);
        }
    }

    void Core::_communicationThread()
    {
        while (isRunning) {
            sendIfCommand();
            readIfResponse();
        }
    }

    void Core::_gameThread()
    {
        Gui::Graphics graphics(_queueManager);
        graphics.init();
        graphics.run(isRunning);
    }
}
