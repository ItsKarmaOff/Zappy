/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.cpp - Place resources + verify with look before incantation
*/

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"
#include "ZappyTypes.hpp"
#include <regex>
#include <sstream>
#include <vector>
#include <random>

Algo::Algo() : _playerPtr(nullptr), _minFoodThreshold(5), 
               _maxFoodTarget(15), _foodNearby(false), _resourceOnCurrentTile(false),
               _explorationSteps(0), _maxExplorationSteps(1), _targetTile(-1),
               _isSearchingResource(false), _isNavigating(false), _navigationTarget(-1),
               _priorityResource(ResourceType::FOOD), _currentLevel(1), _evolutionInProgress(false)
{
    std::random_device rd;
    _rng.seed(rd());
}

Algo::~Algo() {
}

void Algo::setPlayer(std::shared_ptr<Player> player) {
    _player = player;
}

void Algo::setPlayer(Player* player) {
    _playerPtr = player;
}

void Algo::run() {
    Player* player = _player ? _player.get() : _playerPtr;
        
    if (!player) {
        ERROR << "Player not set in Algo::run()";
        return;
    }

    DEBUG << "Starting SMART EVOLUTION algorithm with GROUND VERIFICATION...";
    
    while (player->isAlive()) {
        simpleSurvivalAndEvolution(player);
    }
    
    DEBUG << "Player died or algorithm ended.";
}

void Algo::simpleSurvivalAndEvolution(Player* player) {
    static int cycleCount = 0;
    cycleCount++;
    
    int realLevel = player->getLevel();
    if (realLevel != _currentLevel) {
        DEBUG << "🎉 Level up! " << _currentLevel << " -> " << realLevel;
        _currentLevel = realLevel;
        _evolutionInProgress = false;
    }
    
    if (cycleCount % 15 == 0) {
        player->inventory();
        waitForResponse(player);
    }
    
    player->look();
    waitForResponse(player);
    collectResources(player);
    if (!_evolutionInProgress && canEvolveWithInventory(player)) {
        DEBUG << "=== CAN EVOLVE! Attempting evolution with ground verification ===";
        attemptEvolutionWithVerification(player);
        return;
    }
    simpleExploration(player);
}

bool Algo::canEvolveWithInventory(Player* player) const {
    return player->canEvolveToLevel(_currentLevel + 1);
}

void Algo::attemptEvolutionWithVerification(Player* player) {
    _evolutionInProgress = true;
    
    auto required = player->getRequiredItemsForLevel(_currentLevel + 1);
    
    DEBUG << "📦 Step 1: Placing evolution resources on ground";
    
    for (const auto& req : required) {
        std::string resourceName = resourceTypeToString(req.first);
        int needed = req.second;
        
        for (int i = 0; i < needed; i++) {
            DEBUG << "Setting " << resourceName << " on ground (" << (i+1) << "/" << needed << ")";
            player->set(resourceName);
            waitForResponse(player);
        }
    }
    
    DEBUG << "✅ Step 2: All resources placed, now verifying with Look...";
    
    // Step 2: Look to verify resources are on ground
    player->look();
    waitForResponse(player);
    
    // Step 3: Verify that all required resources are on current tile
    if (verifyResourcesOnGround(required)) {
        DEBUG << "✅ Step 3: Resources confirmed on ground! Launching incantation...";
        player->incantation();
        waitForResponse(player);
    } else {
        DEBUG << "❌ Step 3: Resources NOT found on ground! Aborting evolution.";
        DEBUG << "Current tile content: " << _lastLookResponse;
    }
    
    _evolutionInProgress = false;
}

bool Algo::verifyResourcesOnGround(const std::map<ResourceType, int>& required) {
    // Parse the current tile (tile 0)
    std::vector<std::string> tiles = parseLookResponse(_lastLookResponse);
    
    if (tiles.empty()) {
        DEBUG << "❌ No tiles found in look response";
        return false;
    }
    
    std::string currentTile = tiles[0];
    DEBUG << "🔍 Checking current tile: [" << currentTile << "]";
    
    // Count each required resource on the ground
    for (const auto& req : required) {
        std::string resourceName = resourceTypeToString(req.first);
        int needed = req.second;
        
        // Count occurrences of this resource in the tile
        int found = 0;
        size_t pos = 0;
        while ((pos = currentTile.find(resourceName, pos)) != std::string::npos) {
            found++;
            pos += resourceName.length();
        }
        
        DEBUG << "🔍 Resource " << resourceName << ": found " << found << ", needed " << needed;
        
        if (found < needed) {
            DEBUG << "❌ Not enough " << resourceName << " on ground";
            return false;
        }
    }
    
    DEBUG << "✅ All required resources verified on ground!";
    return true;
}

void Algo::collectResources(Player* player) {
    if (!_resourceOnCurrentTile) {
        return;
    }
    
    DEBUG << "🎯 Collecting resources on current tile";
    
    // Priority: resources needed for evolution, then food
    std::vector<std::string> priorityResources;
    
    auto required = player->getRequiredItemsForLevel(_currentLevel + 1);
    for (const auto& req : required) {
        if (player->getItemCount(req.first) < req.second) {
            priorityResources.push_back(resourceTypeToString(req.first));
        }
    }
    priorityResources.push_back("food");
    
    for (const std::string& resName : priorityResources) {
        if (_lastLookResponse.find(resName) != std::string::npos) {
            DEBUG << "📦 Taking " << resName;
            player->take(resName);
            waitForResponse(player);
            break;
        }
    }
}

void Algo::simpleExploration(Player* player) {
    static int moveCounter = 0;
    moveCounter++;
    
    if (moveCounter % 10 == 0) {
        player->right();
        DEBUG << "Turning right";
    } else {
        player->forward();
        DEBUG << "Moving forward";
    }
    
    waitForResponse(player);
}

void Algo::waitForResponse(Player* player) {
    if (!player->getCommandsQueue()->hasPendingCommand()) {
        return;
    }
    
    std::string expectedCommand = player->getCommandsQueue()->getCurrentPendingCommand();
    
    while (player->isAlive()) {
        while (player->getCommandsQueue()->hasResponses()) {
            std::string response = player->getCommandsQueue()->popResponse();
            
            if (response == "dead") {
                ERROR << "Player died!";
                return;
            }
            
            DEBUG << "📨 Received: " << response;
            
            player->processResponse(response);
            
            bool isResponseForCommand = false;
            
            if (response == "ok" || response == "ko") {
                isResponseForCommand = true;
            } else if (response.find("[") != std::string::npos) {
                if (expectedCommand == "Look" || expectedCommand == "Inventory") {
                    processLookResponse(response);
                    isResponseForCommand = true;
                }
            } else if (response == "Elevation underway" || response.find("Current level:") == 0) {
                if (expectedCommand == "Incantation") {
                    isResponseForCommand = true;
                }
            }
            
            if (isResponseForCommand) {
                DEBUG << "✅ Got response for: " << expectedCommand;
                player->getCommandsQueue()->popPendingCommand();
                return;
            }
        }
    }
}

void Algo::processLookResponse(const std::string& response) {
    if (response.find("food ") != std::string::npos && 
        std::regex_search(response, std::regex(R"(food\s+\d+)"))) {
        return;
    }
    
    _lastLookResponse = response;
    
    std::vector<std::string> tiles = parseLookResponse(response);
    
    _resourceOnCurrentTile = false;
    
    if (!tiles.empty()) {
        std::string currentTile = tiles[0];
        
        std::vector<std::string> resources = {
            "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
        };
        
        for (const std::string& res : resources) {
            if (currentTile.find(res) != std::string::npos) {
                _resourceOnCurrentTile = true;
                DEBUG << "🎯 Found " << res << " on current tile";
                break;
            }
        }
    }
}

std::vector<std::string> Algo::parseLookResponse(const std::string& lookResponse) {
    std::vector<std::string> tiles;
    
    std::string content = lookResponse;
    if (content.front() == '[') content.erase(0, 1);
    if (content.back() == ']') content.pop_back();
    
    std::stringstream ss(content);
    std::string tile;
    
    while (std::getline(ss, tile, ',')) {
        size_t start = tile.find_first_not_of(" \t");
        size_t end = tile.find_last_not_of(" \t");
        
        if (start != std::string::npos) {
            tile = tile.substr(start, end - start + 1);
        } else {
            tile = "";
        }
        
        tiles.push_back(tile);
    }
    
    return tiles;
}