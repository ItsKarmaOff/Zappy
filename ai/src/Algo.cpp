/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.cpp - Improved Smart Food Search Algorithm
*/

#include "Algo.hpp"
#include "Player.hpp"
#include "Lib.hpp"
#include <regex>
#include <sstream>
#include <vector>
#include <random>

Algo::Algo() : _playerPtr(nullptr), _currentFood(10), _minFoodThreshold(3), 
               _maxFoodTarget(20), _foodNearby(false), _foodOnCurrentTile(false),
               _explorationSteps(0), _maxExplorationSteps(1), _targetTile(-1),
               _isSearchingFood(false)
{
    // Initialiser le générateur de nombres aléatoires
    std::random_device rd;
    _rng.seed(rd());
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

    DEBUG << "Starting SMART FOOD SEARCH algorithm...";
    DEBUG << "Strategy: Look before moving, target food intelligently";
    
    while (player->isAlive()) {
        smartSurvivalCycle(player);
    }
    
    DEBUG << "Player died or algorithm ended.";
}

void Algo::smartSurvivalCycle(Player* player)
{
    static int cycleCount = 0;
    cycleCount++;
    
    // Vérifier l'inventaire périodiquement
    if (cycleCount % 10 == 0) {
        player->inventory();
        waitAndProcessResponses(player, 500);
    }
    
    // Prendre de la nourriture si on est sur une case qui en contient
    player->take("food");
    waitAndProcessResponses(player, 200);
    
    // Si on a peu de nourriture, chercher activement
    if (needsFood() || _isSearchingFood) {
        DEBUG << "Low food (" << _currentFood << "), starting smart search...";
        smartFoodSearch(player);
    } else {
        // Exploration normale avec recherche opportuniste
        normalExploration(player);
    }
    
    // Traiter les réponses en attente
    processAllResponses(player);
}

void Algo::smartFoodSearch(Player* player)
{
    _isSearchingFood = true;
    
    // Si on a déjà une cible, aller vers elle
    if (_targetTile >= 0) {
        moveToTargetTile(player);
        return;
    }
    
    // Sinon, regarder autour et trouver une cible
    DEBUG << "Looking around for food...";
    player->look();
    waitAndProcessResponses(player, 500);
    
    // Si on n'a pas trouvé de nourriture visible, explorer aléatoirement
    if (_targetTile < 0) {
        DEBUG << "No food visible, random exploration...";
        randomExploration(player);
    }
    
    // Arrêter la recherche si on a assez de nourriture
    if (_currentFood >= _maxFoodTarget) {
        _isSearchingFood = false;
        _targetTile = -1;
        DEBUG << "Food target reached (" << _currentFood << "), stopping search";
    }
}

void Algo::normalExploration(Player* player)
{
    // Regarder de temps en temps pour des opportunités
    static int lookCounter = 0;
    lookCounter++;
    
    if (lookCounter % 5 == 0) {
        DEBUG << "Opportunistic look around...";
        player->look();
        waitAndProcessResponses(player, 300);
        
        // Si on voit de la nourriture, la prendre
        if (_targetTile >= 0) {
            DEBUG << "Found food opportunity!";
            moveToTargetTile(player);
            return;
        }
    }
    
    // Mouvement d'exploration normal
    if (lookCounter % 7 == 0) {
        player->right();
    } else {
        player->forward();
    }
    waitAndProcessResponses(player, 300);
}

void Algo::randomExploration(Player* player)
{
    std::uniform_int_distribution<int> dist(0, 5);
    int action = dist(_rng);
    
    switch (action) {
        case 0:
        case 1:
            player->right();
            break;
        case 2:
            player->left();
            break;
        default:
            player->forward();
            break;
    }
    waitAndProcessResponses(player, 400);
}

void Algo::moveToTargetTile(Player* player)
{
    if (_targetTile < 0) return;
    
    DEBUG << "Moving towards target tile " << _targetTile;
    
    // Logique pour aller vers la tile cible
    // Tile 0 = position actuelle, tiles 1-3 = devant, etc.
    switch (_targetTile) {
        case 0:
            // Déjà sur la bonne case, prendre la nourriture
            DEBUG << "Already on target tile, taking food";
            player->take("food");
            _targetTile = -1; // Reset target
            break;
            
        case 1:
        case 2:
        case 3:
            // Cases devant nous
            DEBUG << "Moving forward to tile " << _targetTile;
            player->forward();
            break;
            
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            // Cases sur les côtés ou derrière - tourner d'abord
            DEBUG << "Turning to face tile " << _targetTile;
            if (_targetTile <= 6) {
                player->right(); // Tourner à droite pour les tiles de droite
            } else {
                player->left();  // Tourner à gauche pour les tiles de gauche
            }
            break;
    }
    
    waitAndProcessResponses(player, 400);
}

bool Algo::needsFood() const
{
    return _currentFood < _minFoodThreshold;
}

void Algo::processAllResponses(Player* player)
{
    while (player->getCommandsQueue()->hasResponses()) {
        std::string response = player->getCommandsQueue()->popResponse();
        if (response == "dead") {
            return;
        }
        processStructuredResponse(response);
        player->processResponse(response);
    }
}

void Algo::waitAndProcessResponses(Player* player, int waitTimeMs)
{
    int checkInterval = 50;
    int totalWaited = 0;
    bool gotResponse = false;
    
    while (totalWaited < waitTimeMs && player->isAlive()) {
        while (player->getCommandsQueue()->hasResponses()) {
            std::string response = player->getCommandsQueue()->popResponse();
            gotResponse = true;
            
            if (response == "dead") {
                ERROR << "Player died!";
                return;
            } else if (response == "ko") {
                DEBUG << "Command failed (ko)";
            } else if (response == "ok") {
                DEBUG << "Command successful (ok)";
            } else if (response.find("[") != std::string::npos) {
                DEBUG << "Structured response received: " << response;
                processStructuredResponse(response);
            }
            
            player->processResponse(response);
        }
        
        if (gotResponse && waitTimeMs < 500) {
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(checkInterval));
        totalWaited += checkInterval;
    }
}

void Algo::processStructuredResponse(const std::string& response)
{
    // Traiter les réponses d'inventaire
    if (response.find("food") != std::string::npos && 
        std::regex_search(response, std::regex(R"(\d+)"))) {
        updateInventory(response);
    }
    
    // Traiter les réponses de look
    if (response.find("[") == 0 && response.find("]") != std::string::npos) {
        analyzeLookResponse(response);
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
        }
    }
}

void Algo::analyzeLookResponse(const std::string& lookResponse)
{
    DEBUG << "Analyzing look response: " << lookResponse;
    
    // Parser la réponse look: [tile0, tile1, tile2, ...]
    std::vector<std::string> tiles = parseLookResponse(lookResponse);
    
    // Chercher la nourriture dans les tiles visibles
    _targetTile = -1;
    for (size_t i = 0; i < tiles.size(); i++) {
        if (tiles[i].find("food") != std::string::npos) {
            _targetTile = static_cast<int>(i);
            DEBUG << "Food found on tile " << i << " content: [" << tiles[i] << "]";
            break;
        }
    }
    
    if (_targetTile >= 0) {
        DEBUG << "Setting target tile to " << _targetTile;
    } else {
        DEBUG << "No food visible in current field of view";
    }
    
    _lastLookResponse = lookResponse;
}

std::vector<std::string> Algo::parseLookResponse(const std::string& lookResponse)
{
    std::vector<std::string> tiles;
    
    // Enlever les crochets
    std::string content = lookResponse;
    if (content.front() == '[') content.erase(0, 1);
    if (content.back() == ']') content.pop_back();
    
    // Séparer par les virgules
    std::stringstream ss(content);
    std::string tile;
    
    while (std::getline(ss, tile, ',')) {
        // Enlever les espaces en début et fin
        size_t start = tile.find_first_not_of(" \t");
        size_t end = tile.find_last_not_of(" \t");
        
        if (start != std::string::npos) {
            tile = tile.substr(start, end - start + 1);
        } else {
            tile = "";
        }
        
        tiles.push_back(tile);
    }
    
    DEBUG << "Parsed " << tiles.size() << " tiles from look response";
    return tiles;
}

int Algo::parseInventoryForFood(const std::string& inventoryResponse)
{
    std::regex foodRegex(R"(food\s+(\d+))");
    std::smatch match;
    
    if (std::regex_search(inventoryResponse, match, foodRegex)) {
        return std::stoi(match[1].str());
    }
    
    return _currentFood;
}

bool Algo::isFoodNearby(const std::string& lookResponse)
{
    return lookResponse.find("food") != std::string::npos;
}

bool Algo::isFoodOnCurrentTile(const std::string& lookResponse)
{
    std::vector<std::string> tiles = parseLookResponse(lookResponse);
    return !tiles.empty() && tiles[0].find("food") != std::string::npos;
}