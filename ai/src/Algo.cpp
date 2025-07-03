/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo implementation with lock file leader election
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
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

Algo::Algo() 
    : _playerPtr(nullptr), _currentPhase(StrategyPhase::EXPLORATION),
      _currentLevel(1), _myFoodCount(10), _tilesExplored(0), _emptyTileCount(0),
      _currentPos(0, 0), _spiralRadius(1), _spiralSteps(1), _spiralCurrentSteps(0),
      _spiralDirection(1), _spiralFirstDirection(true), _isLeader(false), _forkedPlayers(0)
{
    std::random_device rd;
    _rng.seed(rd());
    
    if (getenv("ZAPPY_IS_CHILD")) {
        _isLeader = false;
        _currentPhase = StrategyPhase::CHILD_SPAWNED;
        DEBUG << "👶 I am a CHILD - will collect food and wait";
    } else {
        _isLeader = tryBecomeLeader();
        
        if (_isLeader) {
            DEBUG << "👑 I am the LEADER - will explore and collect all resources";
            _currentPhase = StrategyPhase::EXPLORATION;
            initSpiralExploration();
        } else {
            DEBUG << "👶 I am a FOLLOWER - leader already exists, will collect food and wait";
            _currentPhase = StrategyPhase::CHILD_SPAWNED;
        }
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
}

Algo::~Algo() {
    if (_isLeader) {
        cleanup();
        killAllChildren();
    }
}

bool Algo::tryBecomeLeader() {
    const std::string lockFile = "zappy_leader.lock";
    
    struct stat buffer;
    if (stat(lockFile.c_str(), &buffer) == 0) {
        DEBUG << "🔒 Lock file exists - another leader is already active";
        return false;
    }
    
    std::ofstream file(lockFile);
    if (file.is_open()) {
        file << getpid() << std::endl;
        file << std::time(nullptr) << std::endl;
        file.close();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        std::ifstream checkFile(lockFile);
        if (checkFile.is_open()) {
            pid_t filePid;
            checkFile >> filePid;
            checkFile.close();
            
            if (filePid == getpid()) {
                DEBUG << "👑 Successfully acquired leadership lock - PID: " << getpid();
                return true;
            } else {
                DEBUG << "🔒 Another process acquired the lock first - PID in file: " << filePid;
                return false;
            }
        }
    }
    
    DEBUG << "❌ Failed to create lock file";
    return false;
}

void Algo::cleanup() {
    const std::string lockFile = "zappy_leader.lock";
    std::ifstream checkFile(lockFile);
    if (checkFile.is_open()) {
        pid_t filePid;
        checkFile >> filePid;
        checkFile.close();
        
        if (filePid == getpid()) {
            if (remove(lockFile.c_str()) == 0) {
                DEBUG << "🧹 Cleaned up leadership lock file";
            } else {
                DEBUG << "❌ Failed to remove lock file";
            }
        }
    }
}

void Algo::killAllChildren() {
    pid_t pgid = getpgrp();
    DEBUG << "💀 Killing process group: " << pgid;
    
    kill(-pgid, SIGTERM);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    kill(-pgid, SIGKILL);
}

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

    DEBUG << "🚀 Starting with role: " << (_isLeader ? "LEADER" : "FOLLOWER");
    
    while (player->isAlive()) {
        executeMainStrategy(player);
    }
}

void Algo::executeMainStrategy(Player* player) {
    switch (_currentPhase) {
        case StrategyPhase::EXPLORATION: {
            if (!_isLeader) {
                DEBUG << "❌ Non-leader trying to explore - switching to follower mode";
                _currentPhase = StrategyPhase::CHILD_SPAWNED;
                return;
            }
            
            player->inventory();
            waitForResponse(player);
            
            int realFood = player->getItemCount(ResourceType::FOOD);
            bool hasAllOtherResources = true;
            for (const auto& needed : _requiredResources) {
                if (needed.first == ResourceType::FOOD) continue;
                
                int realCount = player->getItemCount(needed.first);
                if (realCount < needed.second) {
                    hasAllOtherResources = false;
                    DEBUG << "❌ Missing " << (needed.second - realCount) << " " 
                          << resourceTypeToString(needed.first) << " (have " << realCount << "/" << needed.second << ")";
                    break;
                }
            }
            
            if (hasAllOtherResources && realFood >= 200) {
                DEBUG << "✅ LEADER: All resources collected! Tiles explored: " << _tilesExplored 
                      << " | Real food: " << realFood << " | All other resources: ✅";
                broadcastResourcesCollected(player);
                _currentPhase = StrategyPhase::FORK_PHASE;
            } else {
                DEBUG << "🔍 LEADER: Still collecting - Food: " << realFood << "/200, Other resources: " 
                      << (hasAllOtherResources ? "✅" : "❌");
                exploreAndCollect(player);
            }
            break;
        }
            
        case StrategyPhase::FORK_PHASE:
            if (!_isLeader) {
                DEBUG << "❌ Non-leader trying to fork - switching to follower mode";
                _currentPhase = StrategyPhase::CHILD_SPAWNED;
                return;
            }
            DEBUG << "🥚 LEADER: Forking the full team FIRST";
            forkAllPlayers(player);
            _currentPhase = StrategyPhase::PREPARATION;
            break;
            
        case StrategyPhase::PREPARATION:
            if (!_isLeader) {
                DEBUG << "❌ Non-leader trying to prepare - switching to follower mode";
                _currentPhase = StrategyPhase::CHILD_SPAWNED;
                return;
            }
            DEBUG << "📦 LEADER: Preparing for team - dropping resources AFTER fork";
            prepareForIncantations(player);
            _currentPhase = StrategyPhase::INCANTATION;
            break;
            
        case StrategyPhase::INCANTATION:
            if (!_isLeader) {
                DEBUG << "❌ Non-leader trying to incantate - switching to follower mode";
                _currentPhase = StrategyPhase::CHILD_SPAWNED;
                return;
            }
            DEBUG << "🎭 LEADER: Performing incantations";
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
        DEBUG << "🚨 LOW FOOD: Prioritizing food collection (current: " << _myFoodCount << ")";
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
        
        DEBUG << "📊 LEADER Progress - Tiles: " << _tilesExplored 
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
            
            DEBUG << "🍖 LEADER: Taking food (real inventory: " << realFood << "/200)";
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
                
                DEBUG << "💎 LEADER: Taking " << resourceName 
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
    DEBUG << "🌀 LEADER: Initializing spiral exploration from center";
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
            DEBUG << "🌀 LEADER: Expanding spiral to radius " << _spiralRadius;
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
    for (int i = 0; i < 6; i++) {
        DEBUG << "🥚 LEADER: Forking player " << (i + 1) << "/6";
        player->fork();
        waitForResponse(player);
        _forkedPlayers++;
    }
    DEBUG << "✅ LEADER: All 6 players forked successfully - team of 7 ready";
}

void Algo::prepareForIncantations(Player* player) {
    DEBUG << "📦 LEADER: Dropping all resources except 60 food for survival";
    int myFood = player->getItemCount(ResourceType::FOOD);
    int foodToDrop = std::max(0, myFood - 60);
    for (int i = 0; i < foodToDrop; i++) {
        player->set("food");
        waitForResponse(player);
    }
    DEBUG << "🍖 LEADER: Dropped " << foodToDrop << " food, keeping 60 for survival";
    
    std::vector<std::string> resources = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    for (const std::string& res : resources) {
        int count = player->getItemCount(stringToResourceType(res));
        for (int i = 0; i < count; i++) {
            player->set(res);
            waitForResponse(player);
        }
        if (count > 0) {
            DEBUG << "💎 LEADER: Dropped " << count << " " << res;
        }
    }
    
    DEBUG << "✅ LEADER: All resources prepared on ground, keeping 60 food for survival";
}

void Algo::performAllIncantations(Player* player) {
    DEBUG << "👑 LEADER: Starting incantations immediately (food already on ground)";
    
    for (int level = 2; level <= 8; level++) {
        DEBUG << "🎭 LEADER: Starting incantation for level " << level;
        DEBUG << "✨ LEADER: Performing incantation for level " << level;
        player->incantation();
        waitForResponse(player);
        int realLevel = player->getLevel();
        if (realLevel >= level) {
            DEBUG << "✅ LEADER: Successfully reached level " << realLevel;
            _currentLevel = realLevel;
        }
        
        if (_currentLevel >= 8) {
            DEBUG << "🎉 LEADER: Reached level 8! Mission accomplished!";
            DEBUG << "💀 LEADER: Killing all child processes";
            
            cleanup();
            DEBUG << "🏁 LEADER: Stopping client - mission complete";
            player->setAlive(false);
            return;
        }
    }
    
    DEBUG << "❌ LEADER: Incantation cycle completed but didn't reach level 8";
    cleanup();
    player->setAlive(false);
}

void Algo::handleChildSpawned(Player* player) {
    static bool hasCollectedFood = false;
    
    if (!hasCollectedFood) {
        DEBUG << "👶 CHILD: Just spawned, collecting my food share";
        collectMyFoodShare(player);
        hasCollectedFood = true;
    } else {
        waitAsChild(player);
    }
}

void Algo::collectMyFoodShare(Player* player) {
    int targetFood = 30;
    player->inventory();
    waitForResponse(player);
    int currentFood = player->getItemCount(ResourceType::FOOD);
    
    DEBUG << "🍖 CHILD: Current food: " << currentFood << ", target: " << targetFood;
    
    int searchSteps = 0;
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
            
            DEBUG << "🍖 CHILD: Took food, now have " << currentFood << "/30";
        } else {
            player->forward();
            waitForResponse(player);
            searchSteps++;
            DEBUG << "🍖 CHILD: Moving forward, step " << searchSteps;
        }
        
        if (currentFood >= targetFood) {
            DEBUG << "🍖 CHILD: Reached target food: " << currentFood;
            break;
        }
        
        if (searchSteps > 100) {
            DEBUG << "🍖 CHILD: Search limit reached, stopping at " << currentFood << " food";
            break;
        }
    }
    
    DEBUG << "✅ CHILD: Food collection finished with " << currentFood << " food";
}

void Algo::waitAsChild(Player* player) {
    static int lastCheck = 0;
    lastCheck++;
    if (lastCheck % 100 == 0) {
        int currentLevel = player->getLevel();
        if (currentLevel > _currentLevel) {
            _currentLevel = currentLevel;
            DEBUG << "🎉 CHILD: Level up to " << _currentLevel;
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
    DEBUG << "📢 LEADER: Broadcasted that all resources are collected";
}

void Algo::broadcastMissionComplete(Player* player) {
    std::string message = "MISSION_COMPLETE";
    player->broadcast(message);
    waitForResponse(player);
    DEBUG << "📢 LEADER: Broadcasted mission complete - level 8 reached!";
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
            DEBUG << "📨 " << response;
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