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

    protected:
    private:
        bool _isAlive = true;
        bool _isKing = false;
        int _level = 1;
        int _teamId = 0;
        std::vector<std::pair<std::string, int>> _inventory;
};

#endif