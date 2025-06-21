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

void Player::run()
{
    while (_isAlive) {
        
    }
}

void Player::broadcast(const std::string &message)
{
    _commandsQueue->pushCommand("broadcast " + message);
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::eject()
{
    _commandsQueue->pushCommand("eject");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::fork()
{
    _commandsQueue->pushCommand("fork");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
    if (response == "OK") {
        if (_forkPlayerCallback) {
            _forkPlayerCallback();
        }
    } else {
        DEBUG << "Fork command failed: " << response;
    }
}

void Player::inventory()
{
    _commandsQueue->pushCommand("inventory");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
    if (response != "ko") {
        _inventory.clear();
        std::istringstream iss(response);
        std::string item;
        while (iss >> item) {
            size_t pos = item.find(':');
            if (pos != std::string::npos) {
                std::string itemName = item.substr(0, pos);
                int quantity = std::stoi(item.substr(pos + 1));
                addToInventory(itemName, quantity);
            }
        }
    }
}

void Player::look()
{
    _commandsQueue->pushCommand("look");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });

    std::string response = _commandsQueue->popResponse();

    if (response == "ko") {
        DEBUG << "Look command failed.";
        return;
    }

    std::vector<std::string> tiles;

    if (response.front() == '[' && response.back() == ']') {
        response = response.substr(1, response.size() - 2);
    } else {
        DEBUG << "Invalid look response format: " << response;
        return;
    }

    std::stringstream ss(response);
    std::string tile;

    while (std::getline(ss, tile, ',')) {
        size_t start = tile.find_first_not_of(" \t");
        if (start != std::string::npos)
            tile = tile.substr(start);
        else
            tile.clear();

        tiles.push_back(tile);
    }

    DEBUG << "Look result:";
    for (size_t i = 0; i < tiles.size(); ++i) {
        DEBUG << "Tile[" << i << "]: \"" << tiles[i] << "\"";
    }

    _view = tiles;
}

void Player::forward()
{
    _commandsQueue->pushCommand("forward");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::right()
{
    _commandsQueue->pushCommand("right");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::left()
{
    _commandsQueue->pushCommand("left");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::connect_nbr()
{
    _commandsQueue->pushCommand("connect_nbr");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
}

void Player::take(const std::string &item)
{
    _commandsQueue->pushCommand("take " + item);
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();

    if (response == "ko") {
        DEBUG << "Take command failed for item: " << item;
        return;
    }
    bool itemFound = false;
    for (auto &invItem : _inventory) {
        if (invItem.first == item) {
            invItem.second++;
            itemFound = true;
            break;
        }
    }
    if (!itemFound) {
        _inventory.emplace_back(item, 1);
    }
}

void Player::set(const std::string &item)
{
    _commandsQueue->pushCommand("set " + item);
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();
    if (response == "ko") {
        DEBUG << "Set command failed for item: " << item;
        return;
    }
    bool itemFound = false;
    for (auto &invItem : _inventory) {
        if (invItem.first == item) {
            if (invItem.second > 0) {
                invItem.second--;
                itemFound = true;
            } else {
                DEBUG << "No " << item << " left in inventory to set.";
            }
            break;
        }
    }
    if (!itemFound) {
        DEBUG << "Item " << item << " not found in inventory to set.";
        return;
    }
}

void Player::incantation()
{
    _commandsQueue->pushCommand("incantation");
    std::unique_lock<std::mutex> lock(_commandsQueue->getResponsesQueueMutex());
    _commandsQueue->getResponseCondition().wait(lock, [this] { return _commandsQueue->hasResponses(); });
    std::string response = _commandsQueue->popResponse();

    if (response == "elevation underway") {
        DEBUG << "Incantation started!";
    } else {
        DEBUG << "Incantation failed.";
    } 
}