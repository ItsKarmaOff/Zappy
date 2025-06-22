/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Lib.hpp"
#include "Socket.hpp"
#include "Parser.hpp"
#include "Player.hpp"
#include "CommandsQueue.hpp"

class Engine {
    public:
        Engine(Parser &parser);
        ~Engine();
        void run();
        std::string getResponse();
        void sendCommand(const std::vector<std::string> &command);

    protected:
    private:
        void _init();
        void _communicationThread();
        void _readIfResponse();
        void _sendIfCommand();

        Parser &_parser;
        std::unique_ptr<Lib::Socket> _clientSocket;
        struct sockaddr_in _client;
        std::shared_ptr<Player> _player;
        std::shared_ptr<CommandsQueue> _commandsQueue;
        struct pollfd _pollFd;
        int _amountOfPlayers;
        bool _isRunning;
};

#endif /* !ENGINE_HPP_ */