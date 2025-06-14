/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Parser.hpp"
#include "Socket.hpp"
#include "Lib.hpp"
#include "Player.hpp"
#include "CommandsManager.hpp"
#include "CommandsQueue.hpp"
#include "Algo.hpp"

class Engine {
    public:
        Engine(Parser &parser);
        ~Engine();
        void run();
        std::string getResponse(Lib::Socket *socket);
    protected:
    private:
        void _communicate(Lib::Socket *clientSocket);
        void _init();
        Parser _parser;
        void _createNewPlayer();
        std::shared_ptr<Lib::Socket> _socket;
        struct sockaddr_in _client;
        bool _isRunning = true;
        std::shared_ptr<Player> _player;
        int _amountOfPlayers = 0;
        std::vector<pid_t> _processes;
};

#endif
