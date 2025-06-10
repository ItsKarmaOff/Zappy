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

class Engine {
    public:
        Engine(Parser &parser);
        ~Engine();
        void run();
        std::string getResponse();
        protected:
        private:
        void _communicate();
        void _init();
        Parser _parser;
        std::shared_ptr<Lib::Socket> _clientSocket;
        struct sockaddr_in _client;
        bool _isRunning = true;
        std::unique_ptr<std::thread> _communicationthread;
        std::shared_ptr<Player> _player;
        
};

#endif /* !ENGINE_HPP_ */
