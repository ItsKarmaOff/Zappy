/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Algo.cpp
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
    
    // Détecter si c'est un enfant (spawné par fork)
    if (getenv("ZAPPY_IS_CHILD")) {
        _isLeader = false;
        _currentPhase = StrategyPhase::CHILD_SPAWNED;
        DEBUG << "👶 I am a CHILD - will collect food and wait";
    } else {
        DEBUG << "👑 I am the LEADER - will explore and collect";
    }
    
    // Ressources nécessaires pour tous les niveaux (1->8)
    // Ajusté pour les nouvelles quantités de food
    _requiredResources[ResourceType::FOOD] = 200;        // 40 leader + 5×30 enfants = 190, donc 200 sécurité
    _requiredResources[ResourceType::LINEMATE] = 15;     // Total nécessaire pour tous les niveaux
    _requiredResources[ResourceType::DERAUMERE] = 12;
    _requiredResources[ResourceType::SIBUR] = 15;
    _requiredResources[ResourceType::MENDIANE] = 8;
    _requiredResources[ResourceType::PHIRAS] = 10;
    _requiredResources[ResourceType::THYSTAME] = 3;
    
    // Initialiser les ressources collectées
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

    // Utiliser la variable d'environnement que ton système met en place
    const char* isFollower = getenv("ZAPPY_IS_FOLLOWER");
    
    if (isFollower && strcmp(isFollower, "1") == 0) {
        // C'est un enfant (processus forké)
        _isLeader = false;
        _currentPhase = StrategyPhase::CHILD_SPAWNED;
        DEBUG << "👶 I am a CHILD - ZAPPY_IS_FOLLOWER=1 detected, will collect food and wait";
    } else {
        // C'est le leader (processus principal)
        _isLeader = true;
        _currentPhase = StrategyPhase::EXPLORATION;
        initSpiralExploration();
        DEBUG << "👑 I am the LEADER - will explore and collect all resources";
    }
    
    while (player->isAlive()) {
        executeMainStrategy(player);
    }
}

void Algo::executeMainStrategy(Player* player) {
    switch (_currentPhase) {
        case StrategyPhase::EXPLORATION: {
            // Vérifier les ressources ET la food réelle depuis l'inventaire
            player->inventory();
            waitForResponse(player);
            
            int realFood = player->getItemCount(ResourceType::FOOD);
            
            // Vérifier toutes les autres ressources dans l'inventaire réel
            bool hasAllOtherResources = true;
            for (const auto& needed : _requiredResources) {
                if (needed.first == ResourceType::FOOD) continue; // Skip food, on la vérifie séparément
                
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
                _currentPhase = StrategyPhase::PREPARATION;
            } else {
                DEBUG << "🔍 LEADER: Still collecting - Food: " << realFood << "/200, Other resources: " 
                      << (hasAllOtherResources ? "✅" : "❌");
                exploreAndCollect(player);
            }
            break;
        }
            
        case StrategyPhase::PREPARATION:
            DEBUG << "📦 LEADER: Preparing for team - dropping resources";
            prepareForIncantations(player);
            _currentPhase = StrategyPhase::FORK_PHASE;
            break;
            
        case StrategyPhase::FORK_PHASE:
            DEBUG << "🥚 LEADER: Forking the full team";
            forkAllPlayers(player);
            _currentPhase = StrategyPhase::INCANTATION;
            break;
            
        case StrategyPhase::INCANTATION:
            DEBUG << "🎭 LEADER: Performing incantations";
            performAllIncantations(player);
            break;
            
        case StrategyPhase::CHILD_SPAWNED:
            handleChildSpawned(player);
            break;
    }
}

void Algo::exploreAndCollect(Player* player) {
    // Mettre à jour le food count réel depuis l'inventaire
    player->inventory();
    waitForResponse(player);
    _myFoodCount = player->getItemCount(ResourceType::FOOD);
    
    // Vérifier d'abord si on a assez de food pour survivre
    if (_myFoodCount <= 20) {
        DEBUG << "🚨 LOW FOOD: Prioritizing food collection (current: " << _myFoodCount << ")";
    }
    
    // Regarder la case actuelle
    player->look();
    waitForResponse(player);
    
    // Collecter tout ce qui est sur la case
    collectResourcesOnCurrentTile(player);
    
    // Passer à la case suivante
    moveInSpiral(player);
    _tilesExplored++;
    
    // Log périodique du progrès
    if (_tilesExplored % 50 == 0) {
        // Vérifier la food réelle à chaque log
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
        
        // Vérifier la food réelle dans l'inventaire (pas le compteur)
        player->inventory();
        waitForResponse(player);
        int realFood = player->getItemCount(ResourceType::FOOD);
        
        // Priorité 1: Food si on en a besoin (limite à 200 food réelle)
        if (currentTile.find("food") != std::string::npos && realFood < 200) {
            
            DEBUG << "🍖 LEADER: Taking food (real inventory: " << realFood << "/200)";
            player->take("food");
            waitForResponse(player);
            _myFoodCount = realFood + 1; // Mettre à jour notre compteur
            foundSomething = true;
            
            // Re-regarder pour voir ce qui reste
            player->look();
            waitForResponse(player);
            tiles = parseLookResponse(_lastLookResponse);
            if (tiles.empty()) break;
            currentTile = tiles[0];
            continue;
        }
        
        // Priorité 2: Collecter les autres ressources nécessaires
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
                
                // Re-regarder
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
    _currentPos = Position(0, 0);  // Start at center (relative position)
    _spiralRadius = 1;
    _spiralSteps = 1;
    _spiralCurrentSteps = 0;
    _spiralDirection = 1; // Start going East
    _spiralFirstDirection = true;
}

void Algo::moveInSpiral(Player* player) {
    // Move forward in current direction
    moveForward(player);
    
    // Update position based on direction
    switch(_spiralDirection) {
        case 0: _currentPos.y++; break; // North
        case 1: _currentPos.x++; break; // East  
        case 2: _currentPos.y--; break; // South
        case 3: _currentPos.x--; break; // West
    }
    
    _spiralCurrentSteps++;
    
    // Check if we need to turn
    if (_spiralCurrentSteps >= _spiralSteps) {
        // Turn to next direction (clockwise spiral)
        int nextDirection = (_spiralDirection + 1) % 4;
        turnToDirection(player, nextDirection);
        _spiralDirection = nextDirection;
        
        _spiralCurrentSteps = 0;
        
        // In spiral: after every 2 turns, increase step count
        // Pattern: 1 East, 1 South, 2 West, 2 North, 3 East, 3 South, etc.
        if (_spiralFirstDirection) {
            _spiralFirstDirection = false; // Next direction will have same step count
        } else {
            _spiralSteps++; // Increase steps for next pair of directions
            _spiralFirstDirection = true;
            _spiralRadius++;
            DEBUG << "🌀 LEADER: Expanding spiral to radius " << _spiralRadius;
        }
    }
}

void Algo::turnToDirection(Player* player, int targetDirection) {
    int currentDir = getCurrentDirection();
    
    // Calculate shortest rotation
    int diff = (targetDirection - currentDir + 4) % 4;
    
    if (diff == 1) {
        // Turn right once
        player->right();
        waitForResponse(player);
    } else if (diff == 2) {
        // Turn around (right twice)
        player->right();
        waitForResponse(player);
        player->right();
        waitForResponse(player);
    } else if (diff == 3) {
        // Turn left once (equivalent to right 3 times)
        player->left();
        waitForResponse(player);
    }
    // diff == 0 means already facing correct direction
}

int Algo::getCurrentDirection() const {
    // This is a simplified version - in reality you'd need to track
    // the player's actual facing direction from server responses
    return _spiralDirection;
}

void Algo::forkAllPlayers(Player* player) {
    // Fork 5 joueurs pour avoir un total de 6 (leader + 5)
    for (int i = 0; i < 5; i++) {
        DEBUG << "🥚 LEADER: Forking player " << (i + 1) << "/5";
        player->fork();
        waitForResponse(player);
        _forkedPlayers++;
    }
    DEBUG << "✅ LEADER: All 5 players forked successfully - team of 6 ready";
}

void Algo::prepareForIncantations(Player* player) {
    DEBUG << "📦 LEADER: Dropping all resources except 40 food for survival";
    
    // Garder 40 food pour le leader (au lieu de 25)
    int myFood = player->getItemCount(ResourceType::FOOD);
    int foodToDrop = std::max(0, myFood - 40);
    for (int i = 0; i < foodToDrop; i++) {
        player->set("food");
        waitForResponse(player);
    }
    DEBUG << "🍖 LEADER: Dropped " << foodToDrop << " food, keeping 40 for survival";
    
    // Déposer toutes les autres ressources
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
    
    DEBUG << "✅ LEADER: All resources prepared on ground, keeping 40 food for survival";
}

void Algo::performAllIncantations(Player* player) {
    // Ressources pour chaque niveau selon le PDF
    std::vector<std::map<std::string, int>> levelRequirements = {
        {}, // Level 1 (pas d'incantation)
        {{"linemate", 1}}, // Level 2
        {{"linemate", 1}, {"deraumere", 1}, {"sibur", 1}}, // Level 3
        {{"linemate", 2}, {"sibur", 1}, {"phiras", 2}}, // Level 4
        {{"linemate", 1}, {"deraumere", 1}, {"sibur", 2}, {"phiras", 1}}, // Level 5
        {{"linemate", 1}, {"deraumere", 2}, {"sibur", 1}, {"mendiane", 3}}, // Level 6
        {{"linemate", 1}, {"deraumere", 2}, {"sibur", 3}, {"phiras", 1}}, // Level 7
        {{"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}} // Level 8
    };
    
    // Boucle infinie d'incantations
    while (player->isAlive()) {
        for (int level = 2; level <= 8; level++) {
            DEBUG << "🎭 LEADER: Starting incantation for level " << level;
            
            // Placer les ressources nécessaires pour ce niveau
            for (const auto& req : levelRequirements[level - 1]) {
                for (int i = 0; i < req.second; i++) {
                    player->take(req.first);
                    waitForResponse(player);
                }
            }
            
            // Incanter
            DEBUG << "✨ LEADER: Performing incantation for level " << level;
            player->incantation();
            waitForResponse(player);
            
            // Vérifier le niveau actuel
            int realLevel = player->getLevel();
            if (realLevel >= level) {
                DEBUG << "✅ LEADER: Successfully reached level " << realLevel;
                _currentLevel = realLevel;
            }
            
            // Si on a atteint le niveau 8, recommencer le cycle
            if (_currentLevel >= 8) {
                DEBUG << "🎉 LEADER: Reached level 8! Restarting incantation cycle...";
                break;
            }
        }
        
        // Petite pause avant de recommencer
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Algo::handleChildSpawned(Player* player) {
    static bool hasCollectedFood = false;
    
    if (!hasCollectedFood) {
        DEBUG << "👶 CHILD: Just spawned, collecting my food share";
        collectMyFoodShare(player);
        hasCollectedFood = true;
    } else {
        DEBUG << "😴 CHILD: Waiting for leader's incantations...";
        waitAsChild(player);
    }
}

void Algo::collectMyFoodShare(Player* player) {
    // Chaque enfant récupère 30 food exactement
    int targetFood = 30;
    int currentFood = player->getItemCount(ResourceType::FOOD);
    
    DEBUG << "🍖 CHILD: Current food: " << currentFood << ", target: " << targetFood;
    
    // Compter la food disponible au sol pour vérifier qu'on ne dépasse pas 200 total
    player->look();
    waitForResponse(player);
    std::vector<std::string> tiles = parseLookResponse(_lastLookResponse);
    int foodOnGround = 0;
    if (!tiles.empty()) {
        std::string currentTile = tiles[0];
        size_t pos = 0;
        while ((pos = currentTile.find("food", pos)) != std::string::npos) {
            foodOnGround++;
            pos += 4; // longueur de "food"
        }
    }
    
    DEBUG << "🍖 CHILD: Food visible on ground: " << foodOnGround;
    
    while (currentFood < targetFood && player->isAlive()) {
        // Regarder ce qu'il y a sur la case
        player->look();
        waitForResponse(player);
        
        std::vector<std::string> tiles = parseLookResponse(_lastLookResponse);
        if (!tiles.empty() && tiles[0].find("food") != std::string::npos) {
            // Vérifier qu'on ne prend pas trop (limite globale de 200)
            // Estimation: 5 enfants × 30 + leader 40 = 190, donc on peut prendre jusqu'à 200
            player->take("food");
            waitForResponse(player);
            currentFood++;
            DEBUG << "🍖 CHILD: Took food, now have " << currentFood << "/30";
        } else {
            // Pas de food ici, chercher un peu autour mais pas trop loin
            static int searchSteps = 0;
            if (searchSteps < 2) {
                player->forward();
                waitForResponse(player);
                searchSteps++;
            } else {
                // Arrêter la recherche si pas assez de food
                DEBUG << "🍖 CHILD: Limited food available, stopping at " << currentFood << " food";
                break;
            }
        }
        
        // Arrêt de sécurité : si on approche de la limite globale
        if (currentFood >= 30) {
            break;
        }
    }
    
    DEBUG << "✅ CHILD: Food collection finished with " << currentFood << " food";
}

void Algo::waitAsChild(Player* player) {
    // Les enfants attendent et participent aux incantations quand le leader les initie
    // Ils restent sur place et suivent les incantations
    
    // Vérifier périodiquement le niveau
    static int lastCheck = 0;
    lastCheck++;
    
    if (lastCheck % 100 == 0) {
        int currentLevel = player->getLevel();
        if (currentLevel > _currentLevel) {
            _currentLevel = currentLevel;
            DEBUG << "🎉 CHILD: Level up to " << _currentLevel;
        }
    }
    
    // Petite pause pour éviter le spam
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

bool Algo::hasAllRequiredResources() const {
    // Cette fonction ne peut pas accéder au player, donc on doit vérifier dans executeMainStrategy
    // On la laisse retourner true et on fait la vraie vérification ailleurs
    return true;
}

bool Algo::hasEnoughFood() const {
    // Pour la food, on ne peut pas se fier au compteur _collectedResources
    // car elle se consomme. On doit vérifier l'inventaire réel.
    // Cette fonction sera appelée avec une vérification d'inventaire juste avant
    return true; // On laisse la vérification se faire dans executeMainStrategy
}

void Algo::broadcastResourcesCollected(Player* player) {
    std::string message = "RESOURCES_READY";
    player->broadcast(message);
    waitForResponse(player);
    DEBUG << "📢 LEADER: Broadcasted that all resources are collected";
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