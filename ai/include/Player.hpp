/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Lib.hpp"
#include "Algo.hpp"

#include "CommandsQueue.hpp"

class Player {
    public:
        //class related
        Player(std::string team, std::thread communicationThread);
        ~Player();
        bool isAlive() const { return _isAlive; }
        void setAlive(bool alive) { _isAlive = alive; }
        bool isKing() const { return _isKing; }
        void setKing(bool king) { _isKing = king; }
        int getLevel() const { return _level; }
        void setLevel(int level) { _level = level; }
        std::string getTeamName() const { return _teamName; }
        void setTeamName(const std::string &teamName) { _teamName = teamName; }
        const std::vector<std::pair<std::string, int>>& getInventory() const { return _inventory; }
        void addToInventory(const std::string &item, int quantity);
        std::thread &getCommunicationThread() { return _communicationThread; }
        CommandsQueue &getCommandsQueue() { return *_commandsQueue; }
        void setCommandsQueue(const std::shared_ptr<CommandsQueue> &commandsQueue) { _commandsQueue = commandsQueue; }
        void setForkPlayerCallback(const std::function<void()> &callback) { _forkPlayerCallback = callback; }
        const std::vector<std::string>& getView() const { return _view; }
        void setView(const std::vector<std::string> &view) { _view = view; }
        const std::vector<std::string>& getBroadcastList() const { return _broadcastList; };
        int getBroadcastSize() const { return _broadcastList.size(); }
        void addToBroadcastList(const std::string &message) {
            _broadcastList.push_back(message);
            _bcIndex = (_bcIndex + 1) % _broadcastList.size();  
        }
        std::string getLastBroadcast() const {
            if (_broadcastList.empty()) {
                return "";
            }
            return _broadcastList[_bcIndex];
        }
        //Engine related
        void run();
        //commands
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
        bool _isAlive = true;
        bool _isKing = false;
        int _level = 1;
        std::string _teamName;
        std::vector<std::pair<std::string, int>> _inventory;
        std::vector<std::string> _view;
        std::vector<std::string> _broadcastList;
        int _bcIndex = 0;
        std::thread _communicationThread;
        std::shared_ptr<CommandsQueue> _commandsQueue;
        std::function<void()> _forkPlayerCallback = nullptr;
};

#endif