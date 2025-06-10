/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(Parser &parser) : _parser(parser)
{
}

Engine::~Engine()
{
}

void Engine::run()
{
    _init();

    //_communicationthread = std::make_unique<std::thread>(&Engine::_communicate, this);
    return;
    while (_isRunning) {
        
    }
    if (_communicationthread && _communicationthread->joinable()) {
        _communicationthread->join();
    }
}

std::string Engine::getResponse()
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
        _isRunning = false;
    }
    while (!response.empty() && response.back() == '\n')
        response.pop_back();
    DEBUG << "Received: [" << response << "]";
    return response;
}

void Engine::_communicate()
{
    DEBUG << "Starting communication thread";
    while (_isRunning) {
        try {
            std::string response = getResponse();
            if (response.empty())
                continue;
            DEBUG << "Processing response: " << response;
        } catch (const Lib::Exceptions::Critical &e) {
            ERROR << "Critical error: " << e.what();
            _isRunning = false;
        } catch (const Lib::Exceptions::Warning &e) {
            WARNING << "Warning: " << e.what();
        }
    }
    DEBUG << "Communication thread ended";
}

void Engine::_init()
{
    DEBUG << "Initializing Engine";
    DEBUG << "Init client: IP: " << _parser.getMachine() << " PORT: " << _parser.getPort();
    _clientSocket = std::make_unique<Lib::Socket>(AF_INET, SOCK_STREAM, 0);
    _client.sin_family = AF_INET;
    _client.sin_port = htons(_parser.getPort());
    _client.sin_addr.s_addr = inet_addr(_parser.getMachine().c_str());
    while (_isRunning) {
    if (connect(_clientSocket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
        throw Lib::Exceptions::Critical("Connect failed: " + std::string(strerror(errno)));
    
    if (getResponse() != "WELCOME")
        throw Lib::Exceptions::Critical("Connection failed.");
    send(_clientSocket->getSocket(), (_parser.getName() + "\n").c_str(), _parser.getName().size() + 1, 0);
    std::string response = getResponse();
    if (response == "KO" || response == "0") {
        throw Lib::Exceptions::Critical("Connection failed: " + response);
    }
    DEBUG << "Connected to server: " << response;
}
}
