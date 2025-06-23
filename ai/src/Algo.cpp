/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.cpp - Queue-Safe Survival Algorithm
*/

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"
#include <regex>
#include <sstream>

Algo::Algo() : _playerPtr(nullptr), _currentFood(10), _minFoodThreshold(3), 
               _maxFoodTarget(20), _foodNearby(false), _foodOnCurrentTile(false),
               _explorationSteps(0), _maxExplorationSteps(1)
{
}

Algo::~Algo()
{
}

void Algo::setPlayer(std::shared_ptr<Player> player)
{
    _player = player;
}

void Algo::setPlayer(Player* player)
{
    _playerPtr = player;
}

void Algo::run()
{
    Player* player = _player ? _player.get() : _playerPtr;
        
    if (!player) {
        ERROR << "Player not set in Algo::run()";
        return;
    }

    DEBUG << "Starting QUEUE-SAFE SURVIVAL algorithm...";
    DEBUG << "Strategy: Respect server queue limits (max 10 commands)";
    
    while (player->isAlive()) {
        survivalCycle(player);
    }
    
    DEBUG << "Player died or algorithm ended.";
}

void Algo::survivalCycle(Player* player)
{
    static int cycleCount = 0;
    cycleCount++;
    
    // Simple strategy: queue up commands and let Engine handle the timing
    
    // Check inventory occasionally
    if (cycleCount % 10 == 0) {
        player->inventory();
    }
    
    // Always try to take food
    player->take("food");
    
    // Simple movement pattern
    if (cycleCount % 7 == 0) {
        player->right();
    } else {
        player->forward();
    }
    
    // Process any responses that came back
    while (player->getCommandsQueue()->hasResponses()) {
        std::string response = player->getCommandsQueue()->popResponse();
        if (response == "dead") {
            return;
        }
        processStructuredResponse(response);
        player->processResponse(response);
    }
    
}

bool Algo::needsFood() const
{
    return _currentFood < _minFoodThreshold;
}

void Algo::searchAndTakeFood(Player* player)
{
    player->take("food");
    waitAndProcessResponses(player, 700);
}

void Algo::exploreForFood(Player* player)
{
    player->forward();
    waitAndProcessResponses(player, 700);
}

void Algo::searchPattern(Player* player)
{
    player->forward();
    waitAndProcessResponses(player, 700);
}

void Algo::waitAndProcessResponses(Player* player, int waitTimeMs)
{
    int checkInterval = 50;
    int totalWaited = 0;
    bool gotResponse = false;
    
    DEBUG << "Waiting for server responses (max " << waitTimeMs << "ms)...";
    
    while (totalWaited < waitTimeMs && player->isAlive()) {
        // Check for responses
        while (player->getCommandsQueue()->hasResponses()) {
            std::string response = player->getCommandsQueue()->popResponse();
            gotResponse = true;
            
            DEBUG << "Server response: [" << response << "]";
            
            if (response == "dead") {
                ERROR << "Player died!";
                return;
            } else if (response == "ko") {
                DEBUG << "Command failed (ko)";
            } else if (response == "ok") {
                DEBUG << "Command successful (ok)";
            } else if (response.find("[") != std::string::npos) {
                DEBUG << "Structured response received";
                processStructuredResponse(response);
            } else {
                DEBUG << "Other response: " << response;
            }
            
            player->processResponse(response);
        }
        
        // If we got a response, we can exit early for some commands
        if (gotResponse && waitTimeMs < 500) {
            DEBUG << "Got response early, continuing...";
            break;
        }
        totalWaited += checkInterval;
    }
    
    if (gotResponse) {
        DEBUG << "Response received after " << totalWaited << "ms";
    } else {
        DEBUG << "No response received after " << waitTimeMs << "ms";
    }
}

void Algo::processStructuredResponse(const std::string& response)
{
    // Only process inventory responses (contain numbers)
    if (response.find("food") != std::string::npos && 
        std::regex_search(response, std::regex(R"(\d+)"))) {
        updateInventory(response);
    }
}

void Algo::updateInventory(const std::string& inventoryResponse)
{
    int newFood = parseInventoryForFood(inventoryResponse);
    if (newFood != _currentFood) {
        int oldFood = _currentFood;
        _currentFood = newFood;
        
        if (_currentFood > oldFood) {
            DEBUG << "Food INCREASED: " << oldFood << " -> " << _currentFood << " (+food found!)";
        } else {
            DEBUG << "Food DECREASED: " << oldFood << " -> " << _currentFood << " (time passed)";
        }
        
        if (_currentFood <= 1) {
            ERROR << "CRITICAL: Almost dead! (" << _currentFood << " units)";
        } else if (_currentFood <= 3) {
            ERROR << "WARNING: Very low food! (" << _currentFood << " units)";
        } else if (_currentFood < _minFoodThreshold) {
            DEBUG << "Low food warning (" << _currentFood << " units)";
        } else {
            DEBUG << "Food level OK (" << _currentFood << " units)";
        }
    }
}

void Algo::analyzeLookResponse(const std::string& lookResponse)
{
    // Not used in this simple algorithm
}

int Algo::parseInventoryForFood(const std::string& inventoryResponse)
{
    // Parse: [food 345, sibur 3, phiras 5, ..., deraumere 0]
    std::regex foodRegex(R"(food\s+(\d+))");
    std::smatch match;
    
    if (std::regex_search(inventoryResponse, match, foodRegex)) {
        return std::stoi(match[1].str());
    }
    
    DEBUG << "Could not parse food from inventory: " << inventoryResponse;
    return _currentFood; // Keep current value if parsing fails
}

bool Algo::isFoodNearby(const std::string& lookResponse)
{
    return lookResponse.find("food") != std::string::npos;
}

bool Algo::isFoodOnCurrentTile(const std::string& lookResponse)
{
    return false; // Not used in simple algorithm
}

void Algo::moveRandomly(Player* player)
{
    if (rand() % 4 == 0) {
        player->right();
    } else {
        player->forward();
    }
    waitAndProcessResponses(player, 700);
}