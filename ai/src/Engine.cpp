/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine
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

    for (int i = 0; i < _amountOfPlayers; ++i) {
        DEBUG << "Forking player " << i + 1 << "/" << _amountOfPlayers;
        pid_t pid = fork();
        if (pid < 0) {
            throw Lib::Exceptions::Critical("Fork failed: " + std::string(strerror(errno)));
        } else if (pid == 0) {
            DEBUG << "Forking new player process";
            try {
                _createNewPlayer();
            } catch (const std::exception &e) {
                std::cerr << "Exception in forked player: " << e.what() << std::endl;
                std::exit(1);
            } catch (...) {
                std::cerr << "Unknown exception in forked player." << std::endl;
                std::exit(1);
            }
            DEBUG << "Running player in child process";
            _player->run();
            _player->getCommunicationThread().join();
            exit(0);
        } else {
            _processes.push_back(pid);
            continue;
        }
    }
    
    std::thread communicationThread(&Engine::_communicate, this, _socket.get());
    _player->setCommunicationThread(std::move(communicationThread));
    
    DEBUG << "All players forked, running main player process";
    _player->run();
    _player->getCommunicationThread().join();
    
    for (pid_t pid : _processes) {
        waitpid(pid, nullptr, 0);
    }
    return;
}

std::string Engine::getResponse(Lib::Socket *socket)
{
    char tmp = 0;
    std::string response;
    int readSize = 0;
    readSize = read(socket->getSocket(), &tmp, 1);
    while (readSize > 0) {
        response += tmp;
        if (tmp == '\n')
            break;
        readSize = read(socket->getSocket(), &tmp, 1);
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

void Engine::_communicate(Lib::Socket *clientSocket) {
    int commandsSent = 0;
    const int MAX_PENDING_COMMANDS = 8;
    
    while (_isRunning && _player->isAlive()) {
        //bool gotResponse = false;
        
        while (poll(&_pollFd, 1, 0) > 0 && (_pollFd.revents & POLLIN)) {
            std::string answer = getResponse(clientSocket);
            if (!answer.empty()) {
                //gotResponse = true;
                
                if (answer != "ko") {
                    commandsSent = std::max(0, commandsSent - 1);
                }
                
                if (answer.find("message", 0) == 0) {
                    _player->addToBroadcastList(answer.substr(8));
                }
                else if (answer.find("eject:", 0) == 0) {
                } else if (answer.find("dead", 0) == 0) {
                    DEBUG << "Player " << _player->getTeamName() << " is dead.";
                    _player->setAlive(false);
                    return;
                } else {
                    _player->getCommandsQueue()->pushResponse(answer);
                }
            }
        }
        
        if (commandsSent < MAX_PENDING_COMMANDS && _player->getCommandsQueue()->hasCommands()) {
            std::string command = _player->getCommandsQueue()->popCommand();
            DEBUG << "Sending command: " << command << " (pending: " << commandsSent << "/" << MAX_PENDING_COMMANDS << ")";
            
            std::string commandWithNewline = command + "\n";
            send(clientSocket->getSocket(), commandWithNewline.c_str(), commandWithNewline.size(), 0);
            commandsSent++;
        }
        
        //if (!gotResponse && !_player->getCommandsQueue()->hasCommands()) {
        //    usleep(1000);  // Seulement si vraiment rien à faire
        //}
    }
}
void Engine::_readIfResponse(Lib::Socket *socket)
{
    if (poll(&_pollFd, 1, 0) > 0 && (_pollFd.revents & POLLIN)) {
        std::string answer = getResponse(socket);
        if (!answer.empty()) {
            if (answer.find("message", 0) == 0) {
                _player->addToBroadcastList(answer.substr(8));
            }
            else if (answer.find("eject:", 0) == 0) {
            } else if (answer.find("dead", 0) == 0) {
                DEBUG << "Player " << _player->getTeamName() << " is dead.";
                _player->setAlive(false);
                std::quick_exit(0);
            } else {
                _player->getCommandsQueue()->pushResponse(answer);
            }
        }
    }
}

void Engine::_sendIfCommand(Lib::Socket *socket)
{
    if (_player->getCommandsQueue()->hasCommands()) {
        std::string command = _player->getCommandsQueue()->popCommand();
        DEBUG << "Sending command: " << command;
        
        std::string commandWithNewline = command + "\n";
        send(socket->getSocket(), commandWithNewline.c_str(), commandWithNewline.size(), 0);
    }
}

void Engine::_init()
{
    DEBUG << "Initializing Engine";
    DEBUG << "Init client: IP: " << _parser.getMachine() << " PORT: " << _parser.getPort();

    _socket = std::make_unique<Lib::Socket>(AF_INET, SOCK_STREAM, 0);
    _client.sin_family = AF_INET;
    _client.sin_port = htons(_parser.getPort());
    _client.sin_addr.s_addr = inet_addr(_parser.getMachine().c_str());
    if (connect(_socket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
        throw Lib::Exceptions::Critical("Connect failed: " + std::string(strerror(errno)));

    if (getResponse(_socket.get()) != "WELCOME")
        throw Lib::Exceptions::Critical("Connection failed.");
    DEBUG << "Connected to server: " << _parser.getMachine() << ":" << _parser.getPort() << " as " << _parser.getName();
    send(_socket->getSocket(), (_parser.getName() + "\n").c_str(), _parser.getName().size() + 1, 0);

    std::string response = getResponse(_socket.get());
    DEBUG << "Server response: " << response;
    if (response == "ko") {
        throw Lib::Exceptions::Critical("Connection failed: " + response);
    }
    _amountOfPlayers = std::stoi(response);
    getResponse(_socket.get());
    
    _player = std::make_shared<Player>(_parser.getName());
    auto commandsQueue = std::make_shared<CommandsQueue>();
    _player->setCommandsQueue(commandsQueue);
    
    _pollFd = {_socket->getSocket(), POLLIN, 0};
    _player->setForkPlayerCallback([this]() {
        pid_t pid = fork();
        if (pid < 0) {
            throw Lib::Exceptions::Critical("Fork failed: " + std::string(strerror(errno)));
        } else if (pid == 0) {
            _createNewPlayer();
            _player->run();
            _player->getCommunicationThread().join();
            exit(0);
        } else {
            _processes.push_back(pid);
        }
    });
}

void Engine::_createNewPlayer()
{
    _socket = std::make_unique<Lib::Socket>(AF_INET, SOCK_STREAM, 0);
    _client.sin_family = AF_INET;
    _client.sin_port = htons(_parser.getPort());
    _client.sin_addr.s_addr = inet_addr(_parser.getMachine().c_str());
    if (connect(_socket->getSocket(), (const struct sockaddr *)&_client, sizeof(_client)) == -1)
        throw Lib::Exceptions::Critical("Connect failed: " + std::string(strerror(errno)));

    if (getResponse(_socket.get()) != "WELCOME")
        throw Lib::Exceptions::Critical("Connection failed.");

    send(_socket->getSocket(), (_parser.getName() + "\n").c_str(), _parser.getName().size() + 1, 0);

    std::string response = getResponse(_socket.get());
    if (response == "ko") {
        throw Lib::Exceptions::Critical("Connection failed: " + response);
    }
    response = getResponse(_socket.get());
    DEBUG << "Connected to server: " << response;
    
    _player = std::make_shared<Player>(_parser.getName());
    auto commandsQueue = std::make_shared<CommandsQueue>();
    _player->setCommandsQueue(commandsQueue);
    
    DEBUG << "Creating new player with name: " << _parser.getName();
    _pollFd = {_socket->getSocket(), POLLIN, 0};
    DEBUG << "Setting up fork callback for player";
    _player->setForkPlayerCallback([this]() {
        DEBUG << "Forking player process in callback";
        pid_t pid = fork();
        if (pid < 0) {
            throw Lib::Exceptions::Critical("Fork failed: " + std::string(strerror(errno)));
        } else if (pid == 0) {
            _createNewPlayer();
            _player->run();
            _player->getCommunicationThread().join();
            exit(0);
        } else {
            _processes.push_back(pid);
        }
    });
    std::thread communicationThread(&Engine::_communicate, this, _socket.get());
    _player->setCommunicationThread(std::move(communicationThread));
}