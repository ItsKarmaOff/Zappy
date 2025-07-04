/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Player class implementation
*/
/**
 * @file Player.cpp
 * @brief The Player class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Algo.hpp"

const std::map<int, std::map<ResourceType, int>> Player::EVOLUTION_REQUIREMENTS = {
    {2, {{ResourceType::LINEMATE, 1}}},
    {3, {{ResourceType::LINEMATE, 1}, {ResourceType::DERAUMERE, 1}, {ResourceType::SIBUR, 1}}},
    {4, {{ResourceType::LINEMATE, 2}, {ResourceType::SIBUR, 1}, {ResourceType::PHIRAS, 2}}},
    {5, {{ResourceType::LINEMATE, 1}, {ResourceType::DERAUMERE, 1}, {ResourceType::SIBUR, 2}, {ResourceType::PHIRAS, 1}}},
    {6, {{ResourceType::LINEMATE, 1}, {ResourceType::DERAUMERE, 2}, {ResourceType::SIBUR, 1}, {ResourceType::MENDIANE, 3}}},
    {7, {{ResourceType::LINEMATE, 1}, {ResourceType::DERAUMERE, 2}, {ResourceType::SIBUR, 3}, {ResourceType::PHIRAS, 1}}},
    {8, {{ResourceType::LINEMATE, 2}, {ResourceType::DERAUMERE, 2}, {ResourceType::SIBUR, 2}, {ResourceType::MENDIANE, 2}, {ResourceType::PHIRAS, 2}, {ResourceType::THYSTAME, 1}}}
};

Player::Player(std::string team) : _teamName(team), _alive(true), _waitingForTakeResponse(false) {
    _inventory[ResourceType::FOOD] = 10;
    _inventory[ResourceType::LINEMATE] = 0;
    _inventory[ResourceType::DERAUMERE] = 0;
    _inventory[ResourceType::SIBUR] = 0;
    _inventory[ResourceType::MENDIANE] = 0;
    _inventory[ResourceType::PHIRAS] = 0;
    _inventory[ResourceType::THYSTAME] = 0;
}

Player::~Player() {
    if (_communicationThread.joinable()) {
        _communicationThread.join();
    }
}

void Player::run() {
    auto algo = std::make_shared<Algo>();
    algo->setPlayer(this);
    algo->run();
}

void Player::broadcast(const std::string &message) {
    std::string command = "Broadcast " + message;
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::eject() {
    std::string command = "Eject";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::fork() {
    DEBUG << "Player::fork() called";
    
    std::string command = "Fork";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
    DEBUG << "Fork command sent to server";
    
    if (_forkPlayerCallback) {
        DEBUG << "Fork callback found, executing...";
        _forkPlayerCallback();
        DEBUG << "Fork callback executed";
    } else {
        DEBUG << "No fork callback available!";
    }
}

void Player::inventory() {
    std::string command = "Inventory";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::look() {
    std::string command = "Look";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::forward() {
    std::string command = "Forward";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::right() {
    std::string command = "Right";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::left() {
    std::string command = "Left";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::connect_nbr() {
    std::string command = "Connect_nbr";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

void Player::take(const std::string &item) {
    _lastTakeCommand = item;
    _waitingForTakeResponse = true;
    std::string command = "Take " + item;
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
    DEBUG << "Taking: " << item;
}

void Player::set(const std::string &item) {
    std::string command = "Set " + item;
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
    
    ResourceType type = stringToResourceType(item);
    if (type != ResourceType::UNKNOWN && _inventory[type] > 0) {
        _inventory[type]--;
        DEBUG << "Set " << item << ", remaining: " << _inventory[type];
    }
}

void Player::incantation() {
    std::string command = "Incantation";
    _commandsQueue->pushCommand(command);
    _commandsQueue->pushPendingCommand(command);
}

int Player::getItemCount(ResourceType type) const {
    auto it = _inventory.find(type);
    return (it != _inventory.end()) ? it->second : 0;
}

bool Player::canEvolveToLevel(int targetLevel) const {
    if (EVOLUTION_REQUIREMENTS.find(targetLevel) == EVOLUTION_REQUIREMENTS.end()) {
        return false;
    }
    
    const auto& required = EVOLUTION_REQUIREMENTS.at(targetLevel);
    for (const auto& req : required) {
        if (getItemCount(req.first) < req.second) {
            DEBUG << "Missing " << (req.second - getItemCount(req.first)) 
                  << " " << resourceTypeToString(req.first) << " for level " << targetLevel;
            return false;
        }
    }
    return true;
}

std::map<ResourceType, int> Player::getRequiredItemsForLevel(int targetLevel) const {
    if (EVOLUTION_REQUIREMENTS.find(targetLevel) != EVOLUTION_REQUIREMENTS.end()) {
        return EVOLUTION_REQUIREMENTS.at(targetLevel);
    }
    return {};
}

void Player::processResponse(const std::string &response) {
    DEBUG << "Processing response: [" << response << "]";
    
    if (response == "dead") {
        _alive = false;
        ERROR << "Player died!";
        return;
    }
    
    if (response.find("[") == 0 && response.find("]") != std::string::npos) {
        if (response.find("food ") != std::string::npos && 
            std::regex_search(response, std::regex(R"(food\s+\d+)"))) {
            DEBUG << "Detected inventory response";
            parseInventoryResponse(response);
        } else {
            DEBUG << "Detected look response";
            parseViewResponse(response);
        }
    }
    else if (response == "ok") {
        DEBUG << "Command executed successfully";
        if (_waitingForTakeResponse) {
            ResourceType type = stringToResourceType(_lastTakeCommand);
            if (type != ResourceType::UNKNOWN) {
                _inventory[type]++;
                DEBUG << "Successfully took " << _lastTakeCommand 
                      << ", new count: " << _inventory[type];
            }
            _waitingForTakeResponse = false;
            _lastTakeCommand.clear();
        }
    }
    else if (response == "ko") {
        DEBUG << "Command failed";
        if (_waitingForTakeResponse) {
            DEBUG << "Take failed for: " << _lastTakeCommand;
            _waitingForTakeResponse = false;
            _lastTakeCommand.clear();
        }
    }
    else if (response.find("Current level:") == 0) {
        std::regex levelRegex(R"(Current level:\s*(\d+))");
        std::smatch match;
        if (std::regex_search(response, match, levelRegex)) {
            _level = std::stoi(match[1]);
            DEBUG << "Level confirmed: " << _level;
        }
    }
    else if (response == "Elevation underway") {
        DEBUG << "Incantation started!";
    }
    else if (response.find("message") == 0) {
        DEBUG << "Broadcast received: " << response;
    }
}

void Player::parseViewResponse(const std::string &response) {
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

void Player::parseInventoryResponse(const std::string &response) {
    for (auto& item : _inventory) {
        item.second = 0;
    }
    
    std::string cleanResponse = response.substr(1, response.size() - 2);
    
    std::regex itemRegex(R"((\w+)\s+(\d+))");
    std::sregex_iterator iter(cleanResponse.begin(), cleanResponse.end(), itemRegex);
    std::sregex_iterator end;
    
    while (iter != end) {
        std::string itemName = (*iter)[1];
        int quantity = std::stoi((*iter)[2]);
        
        ResourceType type = stringToResourceType(itemName);
        if (type != ResourceType::UNKNOWN) {
            _inventory[type] = quantity;
            DEBUG << "Inventory: " << itemName << " = " << quantity;
        }
        ++iter;
    }
    
    DEBUG << "Inventory updated - Food: " << getFoodCount();
}

void Player::addToInventory(ResourceType type, int quantity) {
    _inventory[type] += quantity;
    DEBUG << "Added " << quantity << " " << resourceTypeToString(type) 
          << ", total: " << _inventory[type];
}

void Player::handleTakeSuccess(ResourceType type) {
    if (type != ResourceType::UNKNOWN) {
        addToInventory(type, 1);
        DEBUG << "Successfully took " << resourceTypeToString(type);
    }
}

ResourceType Player::stringToResourceType(const std::string &str) const {
    return ::stringToResourceType(str);
}

std::string Player::resourceTypeToString(ResourceType type) const {
    return ::resourceTypeToString(type);
}

bool Player::hasPendingBroadcasts() const {
    bool hasBroadcasts = !_broadcastQueue.empty();
    if (hasBroadcasts) {
        DEBUG << "hasPendingBroadcasts() = TRUE, queue size: " << _broadcastQueue.size();
    }
    return hasBroadcasts;
}

std::string Player::getNextBroadcast() {
    if (_broadcastQueue.empty()) {
        DEBUG << "getNextBroadcast() called but queue is EMPTY!";
        return "";
    }
    
    std::string broadcast = _broadcastQueue.front();
    _broadcastQueue.pop();
    DEBUG << "Retrieved broadcast from queue: [" << broadcast << "] - Queue size now: " << _broadcastQueue.size();
    return broadcast;
}