/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Commands
*/

#ifndef COMMANDS_MANAGER_HPP_
#define COMMANDS_MANAGER_HPP_

#include "Socket.hpp"
#include "Lib.hpp"
#include "Exceptions.hpp"
#include "CommandsQueue.hpp"

class CommandsManager {
    public:
        CommandsManager(std::shared_ptr<Lib::Socket> clientSocket, std::shared_ptr<CommandsQueue> commandsQueue);
        ~CommandsManager();
        void broadcast(const std::string &message);
        void eject();
        void fork();
        void inventory();
        void look();
        void forward();
        void right();
        void left();
        void connect_nbr();
        void take(const std::string &item);
        void set(const std::string &item);
        void incantation();

    protected:
    private:
        std::shared_ptr<Lib::Socket> _clientSocket;
        std::shared_ptr<CommandsQueue> _queue;

};

#endif
