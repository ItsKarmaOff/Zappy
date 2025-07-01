/*
** EPITECH PROJECT, 2025
** Zappy
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
        std::string getResponse(Lib::Socket *socket);

    protected:
    private:
        void _init();
        void _createNewPlayer();
        void _communicate(Lib::Socket *clientSocket);
        void _readIfResponse(Lib::Socket *socket);
        void _sendIfCommand(Lib::Socket *socket);

        Parser &_parser;
        std::unique_ptr<Lib::Socket> _socket;
        struct sockaddr_in _client;
        std::shared_ptr<Player> _player;
        struct pollfd _pollFd;
        int _amountOfPlayers;
        bool _isRunning;
        std::vector<pid_t> _processes;
};

#endif /* !ENGINE_HPP_ */