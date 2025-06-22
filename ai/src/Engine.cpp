/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine - Version Simplifiée
*/

#include "Engine.hpp"

Engine::Engine(Parser &parser) : _parser(parser), _isRunning(true)
{
}

Engine::~Engine()
{
}

void Engine::run()
{
    _init();
    
    std::thread communicationThread(&Engine::_communicationThread, this);
    _player->run();
    if (communicationThread.joinable()) {
        communicationThread.join();
    }
}

std::string Engine::getResponse()
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
        _isRunning = false;
    }
    
    while (!response.empty() && response.back() == '\n')
        response.pop_back();
        
    if (!response.empty())
        DEBUG << "Received: [" << response << "]";
        
    return response;
}

void Engine::sendCommand(const std::vector<std::string> &command)
{
    std::string commandStr;
    for (std::size_t index = 0; index < command.size(); index++) {
        if (index != 0)
            commandStr += " ";
        commandStr += command[index];
    }
    DEBUG << "Send command: [" << commandStr << "]";
    std::string cmdWithNewline = commandStr + "\n";
    if (send(_clientSocket->getSocket(), cmdWithNewline.c_str(), cmdWithNewline.size(), 0) < 0) {
        ERROR << "Server closed the connection.";
        _isRunning = false;
    }
}

void Engine::_readIfResponse()
{
    if (poll(&_pollFd, 1, 0) > 0 && (_pollFd.revents & POLLIN)) {
        std::string answer = getResponse();
        if (!answer.empty()) {
            if (answer.find("message", 0) == 0) {
                _player->addToBroadcastList(answer.substr(8));
            }
            else if (answer.find("eject:", 0) == 0) {
            } 
            else if (answer.find("dead", 0) == 0) {
                DEBUG << "Player " << _player->getTeamName() << " is dead.";
                _player->setAlive(false);
                _isRunning = false;
            } 
            else {
                _player->processResponse(answer);
            }
        }
    }
}

void Engine::_sendIfCommand()
{
    if (_commandsQueue->hasCommands()) {
        std::vector<std::string> command = _commandsQueue->popCommand();
        if (!command.empty())
            sendCommand(command);
    }
}

void Engine::_communicationThread()
{
    while (_isRunning && _player->isAlive()) {
        _sendIfCommand();
        _readIfResponse();
    }
}

void Engine::_init()
{
    DEBUG << "Initializing Engine";
    DEBUG << "Init client: IP: " << _parser.getMachine() << " PORT: " << _parser.getPort();

    _clientSocket = std::make_unique<Lib::Socket>(AF_INET, SOCK_STREAM, 0);
    _client.sin_family = AF_INET;
    _client.sin_port = htons(_parser.getPort());
    _client.sin_addr.s_addr = inet_addr(_parser.getMachine().c_str());
    
    if (connect(_clientSocket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
        throw Lib::Exceptions::Critical("Connect failed: " + std::string(strerror(errno)));

    if (getResponse() != "WELCOME")
        throw Lib::Exceptions::Critical("Connection failed.");
        
    DEBUG << "Connected to server: " << _parser.getMachine() << ":" << _parser.getPort() << " as " << _parser.getName();
    sendCommand({_parser.getName()});

    std::string response = getResponse();
    DEBUG << "Server response: " << response;
    if (response == "ko") {
        throw Lib::Exceptions::Critical("Connection failed: " + response);
    }
    
    _amountOfPlayers = std::stoi(response);
    getResponse();
    
    _commandsQueue = std::make_shared<CommandsQueue>();
    _player = std::make_shared<Player>(_parser.getName());
    _player->setCommandsQueue(_commandsQueue);
    
    _pollFd = {_clientSocket->getSocket(), POLLIN, 0};
}