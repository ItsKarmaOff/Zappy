/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** The Algo implementation
** Algo
*/
/**
 * @file Algo.cpp
 * @brief The Algo class for Zappy AI
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"
#include "ZappyTypes.hpp"
#include <regex>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstring>

Algo::Algo() 
    : _playerPtr(nullptr), _currentPhase(StrategyPhase::EXPLORATION),
      _currentLevel(1), _myFoodCount(10), _tilesExplored(0), _emptyTileCount(0),
      _currentPos(0, 0), _spiralRadius(1), _spiralSteps(1), _spiralCurrentSteps(0),
      _spiralDirection(1), _spiralFirstDirection(true), _isLeader(true), _forkedPlayers(0)
{
    std::random_device rd;
    _rng.seed(rd());
    
    if (getenv("ZAPPY_IS_CHILD")) {
        _isLeader = false;
        _currentPhase = StrategyPhase::CHILD_SPAWNED;
        DEBUG << "I am a CHILD - will collect food and wait";
    } else {
        DEBUG << "I am the LEADER - will explore and collect";
    }
    
    _requiredResources[ResourceType::FOOD] = 200;
    _requiredResources[ResourceType::LINEMATE] = 15;
    _requiredResources[ResourceType::DERAUMERE] = 12;
    _requiredResources[ResourceType::SIBUR] = 15;
    _requiredResources[ResourceType::MENDIANE] = 8;
    _requiredResources[ResourceType::PHIRAS] = 10;
    _requiredResources[ResourceType::THYSTAME] = 3;
    
    for (const auto& res : _requiredResources) {
        _collectedResources[res.first] = 0;
    }
    
    if (_isLeader) {
        initSpiralExploration();
    }
}

Algo::~Algo() {}

void Algo::setPlayer(std::shared_ptr<Player> player) {
    _player = player;
    _playerPtr = nullptr;
}

void Algo::setPlayer(Player* player) {
    _playerPtr = player;
    _player.reset();
}

Player* Algo::getPlayer() {
    if (_player) return _player.get();
    if (_playerPtr) return _playerPtr;
    ERROR << "No player set!";
    return nullptr;
}

void Algo::run() {
    Player* player = getPlayer();
    if (!player) return;

    const char* isFollower = getenv("ZAPPY_IS_FOLLOWER");
    
    if (isFollower && strcmp(isFollower, "1") == 0) {
        _isLeader = false;
        _currentPhase = StrategyPhase::CHILD_SPAWNED;
        DEBUG << "I am a CHILD - ZAPPY_IS_FOLLOWER=1 detected, will collect food and wait";
    } else {
        _isLeader = true;
        _currentPhase = StrategyPhase::EXPLORATION;
        initSpiralExploration();
        DEBUG << "I am the LEADER - will explore and collect all resources";
    }
    
    while (player->isAlive()) {
        executeMainStrategy(player);
    }
}

void Algo::executeMainStrategy(Player* player) {
    switch (_currentPhase) {
        case StrategyPhase::EXPLORATION: {
            player->inventory();
            waitForResponse(player);
            
            int realFood = player->getItemCount(ResourceType::FOOD);
            
            bool hasAllOtherResources = true;
            for (const auto& needed : _requiredResources) {
                if (needed.first == ResourceType::FOOD) continue;
                
                int realCount = player->getItemCount(needed.first);
                if (realCount < needed.second) {
                    hasAllOtherResources = false;
                    DEBUG << "Missing " << (needed.second - realCount) << " " 
                          << resourceTypeToString(needed.first) << " (have " << realCount << "/" << needed.second << ")";
                    break;
                }
            }
            
            if (hasAllOtherResources && realFood >= 200) {
                DEBUG << "LEADER: All resources collected! Tiles explored: " << _tilesExplored 
                      << " | Real food: " << realFood << " | All other resources: complete";
                broadcastResourcesCollected(player);
                _currentPhase = StrategyPhase::FORK_PHASE;
            } else {
                DEBUG << "LEADER: Still collecting - Food: " << realFood << "/200, Other resources: " 
                      << (hasAllOtherResources ? "complete" : "incomplete");
                exploreAndCollect(player);
            }
            break;
        }
            
        case StrategyPhase::FORK_PHASE:
            DEBUG << "LEADER: Forking the full team FIRST";
            forkAllPlayers(player);
            _currentPhase = StrategyPhase::PREPARATION;
            break;
            
        case StrategyPhase::PREPARATION:
            DEBUG << "LEADER: Preparing for team - dropping resources AFTER fork";
            prepareForIncantations(player);
            _currentPhase = StrategyPhase::INCANTATION;
            break;
            
        case StrategyPhase::INCANTATION:
            DEBUG << "LEADER: Performing incantations";
            performAllIncantations(player);
            break;
            
        case StrategyPhase::CHILD_SPAWNED:
            handleChildSpawned(player);
            break;
    }
}

void Algo::exploreAndCollect(Player* player) {
    player->inventory();
    waitForResponse(player);
    _myFoodCount = player->getItemCount(ResourceType::FOOD);
    
    if (_myFoodCount <= 20) {
        DEBUG << "LOW FOOD: Prioritizing food collection (current: " << _myFoodCount << ")";
    }
    
    player->look();
    waitForResponse(player);
    
    collectResourcesOnCurrentTile(player);
    
    moveInSpiral(player);
    _tilesExplored++;
    
    if (_tilesExplored % 50 == 0) {
        player->inventory();
        waitForResponse(player);
        int realFood = player->getItemCount(ResourceType::FOOD);
        
        DEBUG << "LEADER Progress - Tiles: " << _tilesExplored 
              << " | Spiral radius: " << _spiralRadius
              << " | Pos: (" << _currentPos.x << "," << _currentPos.y << ")"
              << " | Real Food: " << realFood << "/200"
              << " | Linemate: " << _collectedResources[ResourceType::LINEMATE] << "/" << _requiredResources[ResourceType::LINEMATE];
    }
}

void Algo::collectResourcesOnCurrentTile(Player* player) {
    std::vector<std::string> tiles = parseLookResponse(_lastLookResponse);
    if (tiles.empty()) return;
    
    std::string currentTile = tiles[0];
    
    bool foundSomething = true;
    while (foundSomething) {
        foundSomething = false;
        
        player->inventory();
        waitForResponse(player);
        int realFood = player->getItemCount(ResourceType::FOOD);
        
        if (currentTile.find("food") != std::string::npos && realFood < 200) {
            DEBUG << "LEADER: Taking food (real inventory: " << realFood << "/200)";
            player->take("food");
            waitForResponse(player);
            _myFoodCount = realFood + 1;
            foundSomething = true;
            
            player->look();
            waitForResponse(player);
            tiles = parseLookResponse(_lastLookResponse);
            if (tiles.empty()) break;
            currentTile = tiles[0];
            continue;
        }
        
        for (const auto& needed : _requiredResources) {
            if (needed.first == ResourceType::FOOD) continue;
            
            std::string resourceName = resourceTypeToString(needed.first);
            
            if (currentTile.find(resourceName) != std::string::npos && 
                _collectedResources[needed.first] < needed.second) {
                
                DEBUG << "LEADER: Taking " << resourceName 
                      << " (" << _collectedResources[needed.first] << "/" << needed.second << ")";
                player->take(resourceName);
                waitForResponse(player);
                _collectedResources[needed.first]++;
                foundSomething = true;
                
                player->look();
                waitForResponse(player);
                tiles = parseLookResponse(_lastLookResponse);
                if (tiles.empty()) break;
                currentTile = tiles[0];
                break;
            }
        }
    }
}

void Algo::initSpiralExploration() {
    DEBUG << "LEADER: Initializing spiral exploration from center";
    _currentPos = Position(0, 0);
    _spiralRadius = 1;
    _spiralSteps = 1;
    _spiralCurrentSteps = 0;
    _spiralDirection = 1;
    _spiralFirstDirection = true;
}

void Algo::moveInSpiral(Player* player) {
    moveForward(player);
    
    switch(_spiralDirection) {
        case 0: _currentPos.y++; break;
        case 1: _currentPos.x++; break;
        case 2: _currentPos.y--; break;
        case 3: _currentPos.x--; break;
    }
    
    _spiralCurrentSteps++;
    
    if (_spiralCurrentSteps >= _spiralSteps) {
        int nextDirection = (_spiralDirection + 1) % 4;
        turnToDirection(player, nextDirection);
        _spiralDirection = nextDirection;
        
        _spiralCurrentSteps = 0;
        
        if (_spiralFirstDirection) {
            _spiralFirstDirection = false;
        } else {
            _spiralSteps++;
            _spiralFirstDirection = true;
            _spiralRadius++;
            DEBUG << "LEADER: Expanding spiral to radius " << _spiralRadius;
        }
    }
}

void Algo::turnToDirection(Player* player, int targetDirection) {
    int currentDir = getCurrentDirection();
    
    int diff = (targetDirection - currentDir + 4) % 4;
    
    if (diff == 1) {
        player->right();
        waitForResponse(player);
    } else if (diff == 2) {
        player->right();
        waitForResponse(player);
        player->right();
        waitForResponse(player);
    } else if (diff == 3) {
        player->left();
        waitForResponse(player);
    }
}

int Algo::getCurrentDirection() const {
    return _spiralDirection;
}

void Algo::forkAllPlayers(Player* player) {
    for (int i = 0; i < 5; i++) {
        DEBUG << "LEADER: Forking player " << (i + 1) << "/5";
        player->fork();
        waitForResponse(player);
        _forkedPlayers++;
    }
    DEBUG << "LEADER: All 5 players forked successfully - team of 6 ready";
}

void Algo::prepareForIncantations(Player* player) {
    DEBUG << "LEADER: Dropping all resources except 40 food for survival";
    
    int myFood = player->getItemCount(ResourceType::FOOD);
    int foodToDrop = std::max(0, myFood - 40);
    for (int i = 0; i < foodToDrop; i++) {
        player->set("food");
        waitForResponse(player);
    }
    DEBUG << "LEADER: Dropped " << foodToDrop << " food, keeping 40 for survival";
    
    std::vector<std::string> resources = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    for (const std::string& res : resources) {
        int count = player->getItemCount(stringToResourceType(res));
        for (int i = 0; i < count; i++) {
            player->set(res);
            waitForResponse(player);
        }
        if (count > 0) {
            DEBUG << "LEADER: Dropped " << count << " " << res;
        }
    }
    
    DEBUG << "LEADER: All resources prepared on ground, keeping 40 food for survival";
}

void Algo::performAllIncantations(Player* player) {
    DEBUG << "LEADER: Starting incantations immediately (food already on ground)";
    
    while (player->isAlive()) {
        for (int level = 2; level <= 8; level++) {
            DEBUG << "LEADER: Starting incantation for level " << level;
            
            DEBUG << "LEADER: Performing incantation for level " << level;
            player->incantation();
            waitForResponse(player);
            
            int realLevel = player->getLevel();
            if (realLevel >= level) {
                DEBUG << "LEADER: Successfully reached level " << realLevel;
                _currentLevel = realLevel;
            }
            
            if (_currentLevel >= 8) {
                DEBUG << "LEADER: Reached level 8! Restarting incantation cycle...";
                break;
            }
        }
    }
}

void Algo::handleChildSpawned(Player* player) {
    static bool hasCollectedFood = false;
    
    if (!hasCollectedFood) {
        DEBUG << "CHILD: Just spawned, collecting my food share";
        collectMyFoodShare(player);
        hasCollectedFood = true;
    } else {
        DEBUG << "CHILD: Waiting for leader's incantations...";
        waitAsChild(player);
    }
}

void Algo::collectMyFoodShare(Player* player) {
    int targetFood = 30;
    
    player->inventory();
    waitForResponse(player);
    int currentFood = player->getItemCount(ResourceType::FOOD);
    
    DEBUG << "CHILD: Current food: " << currentFood << ", target: " << targetFood;
    
    while (currentFood < targetFood && player->isAlive()) {
        player->look();
        waitForResponse(player);
        
        std::vector<std::string> tiles = parseLookResponse(_lastLookResponse);
        if (!tiles.empty() && tiles[0].find("food") != std::string::npos) {
            player->take("food");
            waitForResponse(player);
            
            player->inventory();
            waitForResponse(player);
            currentFood = player->getItemCount(ResourceType::FOOD);
            
            DEBUG << "CHILD: Took food, now have " << currentFood << "/30";
        } else {
            static int searchSteps = 0;
            if (searchSteps < 2) {
                player->forward();
                waitForResponse(player);
                searchSteps++;
            } else {
                DEBUG << "CHILD: Limited food available, stopping at " << currentFood << " food";
                break;
            }
        }
        
        if (currentFood >= 30) {
            break;
        }
    }
    
    DEBUG << "CHILD: Food collection finished with " << currentFood << " food";
}

void Algo::waitAsChild(Player* player) {
    static int lastCheck = 0;
    lastCheck++;
    
    if (lastCheck % 100 == 0) {
        int currentLevel = player->getLevel();
        if (currentLevel > _currentLevel) {
            _currentLevel = currentLevel;
            DEBUG << "CHILD: Level up to " << _currentLevel;
        }
    }
    
    for (int i = 0; i < 1000; ++i) {
    }
}

bool Algo::hasAllRequiredResources() const {
    return true;
}

bool Algo::hasEnoughFood() const {
    return true;
}

void Algo::broadcastResourcesCollected(Player* player) {
    std::string message = "RESOURCES_READY";
    player->broadcast(message);
    waitForResponse(player);
    DEBUG << "LEADER: Broadcasted that all resources are collected";
}

void Algo::moveForward(Player* player) {
    player->forward();
    waitForResponse(player);
}

void Algo::moveRight(Player* player) {
    player->right();
    waitForResponse(player);
}

void Algo::moveLeft(Player* player) {
    player->left();
    waitForResponse(player);
}

void Algo::processLookResponse(const std::string& response) {
    _lastLookResponse = response;
}

std::vector<std::string> Algo::parseLookResponse(const std::string& lookResponse) const {
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
            
            DEBUG << "Response: " << response;
            
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
                player->getCommandsQueue()->popPendingCommand();
                return;
            }
        }
    }
}