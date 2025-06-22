/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Lib.hpp"
#include "CommandsQueue.hpp"

class Algo;

class Player {
    public:
        Player(std::string team);
        ~Player();
        void run();
        
        void forward();
        void right();
        void left();
        void look();
        void inventory();
        void broadcast(const std::string &message);
        void connect_nbr();
        void fork();
        void eject();
        void take(const std::string &item);
        void set(const std::string &item);
        void incantation();

        const std::string &getTeamName() const { return _teamName; }
        bool isAlive() const { return _alive; }
        const std::vector<std::pair<std::string, int>> &getInventory() const { return _inventory; }
        const std::vector<std::string> &getView() const { return _view; }
        std::shared_ptr<CommandsQueue> getCommandsQueue() const { return _commandsQueue; }
        std::thread &getCommunicationThread() { return _communicationThread; }

        void setAlive(bool alive) { _alive = alive; }
        void setCommandsQueue(std::shared_ptr<CommandsQueue> queue) { _commandsQueue = queue; }
        void setCommunicationThread(std::thread &&thread) { _communicationThread = std::move(thread); }
        void addToBroadcastList(const std::string &message) { _broadcastMessages.push_back(message); }
        void addToInventory(const std::string &item, int quantity);
        void setForkPlayerCallback(std::function<void()> callback) { _forkPlayerCallback = callback; }

        void processResponse(const std::string &response);

    protected:
    private:
        void parseViewResponse(const std::string &response);
        void parseInventoryResponse(const std::string &response);

        std::string _teamName;
        bool _alive;
        std::vector<std::pair<std::string, int>> _inventory;
        std::vector<std::string> _view;
        std::vector<std::string> _broadcastMessages;
        std::shared_ptr<CommandsQueue> _commandsQueue;
        std::thread _communicationThread;
        std::function<void()> _forkPlayerCallback;
};

#endif /* !PLAYER_HPP_ */