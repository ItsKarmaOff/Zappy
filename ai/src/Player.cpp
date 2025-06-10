/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::string team) : _teamName(team)
{
}

Player::~Player()
{
}

void Player::addToInventory(const std::string &item, int quantity)
{
    for (auto &invItem : _inventory) {
        if (invItem.first == item) {
            invItem.second += quantity;
            return;
        }
    }
    _inventory.emplace_back(item, quantity);
}