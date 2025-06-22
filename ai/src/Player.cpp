/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Player
*/

#include "Player.hpp"
#include "Algo.hpp"

Player::Player(std::string team) : _teamName(team), _alive(true)
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
    auto algo = std::make_shared<Algo>();
    algo->setPlayer(this);
    algo->run();
}

void Player::broadcast(const std::string &message)
{
    _commandsQueue->pushCommand("Broadcast " + message);
}

void Player::eject()
{
    _commandsQueue->pushCommand("Eject");
}

void Player::fork()
{
    _commandsQueue->pushCommand("Fork");
}

void Player::inventory()
{
    _commandsQueue->pushCommand("Inventory");
}

void Player::look()
{
    _commandsQueue->pushCommand("Look");
}

void Player::forward()
{
    _commandsQueue->pushCommand("Forward");
}

void Player::right()
{
    _commandsQueue->pushCommand("Right");
}

void Player::left()
{
    _commandsQueue->pushCommand("Left");
}

void Player::connect_nbr()
{
    _commandsQueue->pushCommand("Connect_nbr");
}

void Player::take(const std::string &item)
{
    _commandsQueue->pushCommand("Take " + item);
}

void Player::set(const std::string &item)
{
    _commandsQueue->pushCommand("Set " + item);
}

void Player::incantation()
{
    _commandsQueue->pushCommand("Incantation");
}

void Player::processResponse(const std::string &response)
{
    DEBUG << "Processing response: [" << response << "]";
    
    if (response.find("[") == 0 && response.find("]") != std::string::npos) {
        parseViewResponse(response);
    }
    else if (response.find("food") != std::string::npos && response.find("[") == 0) {
        parseInventoryResponse(response);
    }
    else if (response == "ok") {
        DEBUG << "Command executed successfully";
    }
    else if (response == "ko") {
        DEBUG << "Command failed";
    }
    else if (response == "Elevation underway") {
        DEBUG << "Incantation started!";
    }
    else if (response.find("Current level:") == 0) {
        DEBUG << "Level up: " << response;
    }
    else if (response == "ok" && _forkPlayerCallback) {
        DEBUG << "Fork successful, calling callback";
        _forkPlayerCallback();
    }
}

void Player::parseViewResponse(const std::string &response)
{
    std::vector<std::string> tiles;
    std::string cleanResponse = response.substr(1, response.size() - 2);
    std::stringstream ss(cleanResponse);
    std::string tile;

    while (std::getline(ss, tile, ',')) {
        size_t start = tile.find_first_not_of(" \t");
        if (start != std::string::npos)
            tile = tile.substr(start);
        else
            tile.clear();
        tiles.push_back(tile);
    }
    
    _view = tiles;
    DEBUG << "Look processed: " << tiles.size() << " tiles";
}

void Player::parseInventoryResponse(const std::string &response)
{
    _inventory.clear();
    std::string cleanResponse = response.substr(1, response.size() - 2);
    
    std::istringstream iss(cleanResponse);
    std::string item;
    while (iss >> item) {
        size_t pos = item.find(':');
        if (pos != std::string::npos) {
            std::string itemName = item.substr(0, pos);
            if (itemName.back() == ',') {
                itemName.pop_back();
            }
            int quantity = std::stoi(item.substr(pos + 1));
            addToInventory(itemName, quantity);
        }
    }
    DEBUG << "Inventory processed";
}