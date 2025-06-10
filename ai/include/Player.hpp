/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Lib.hpp"

class Player {
    public:
        Player(std::string team);
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
    protected:
    private:
        bool _isAlive = true;
        bool _isKing = false;
        int _level = 1;
        std::string _teamName;
        std::vector<std::pair<std::string, int>> _inventory;
};

#endif