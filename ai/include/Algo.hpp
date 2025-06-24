/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.hpp - Ultra Simplified
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <random>
#include "ZappyTypes.hpp"
#include <map>

// Forward declaration
class Player;

class Algo {
public:
    Algo();
    ~Algo();
    
    // Player management
    void setPlayer(std::shared_ptr<Player> player);
    void setPlayer(Player* player);
    
    // Main algorithm
    void run();

private:
    // Core cycle
    void simpleSurvivalAndEvolution(Player* player);
    
    // Evolution
    bool canEvolveWithInventory(Player* player) const;
    void attemptEvolution(Player* player);
    
    // Resource collection
    void collectResources(Player* player);
    
    // Movement
    void simpleExploration(Player* player);
    void attemptEvolutionWithVerification(Player* player);
    // Response handling
    void waitForResponse(Player* player);
    void processLookResponse(const std::string& response);
    std::vector<std::string> parseLookResponse(const std::string& lookResponse);
    bool verifyResourcesOnGround(const std::map<ResourceType, int>& required);
    
    // Player references
    std::shared_ptr<Player> _player;
    Player* _playerPtr;
    
    // Simple state
    int _minFoodThreshold;
    int _maxFoodTarget;
    bool _foodNearby;
    bool _resourceOnCurrentTile;
    int _explorationSteps;

    int _maxExplorationSteps;
    int _targetTile;
    bool _isSearchingResource;
    bool _isNavigating;
    int _navigationTarget;
    ResourceType _priorityResource;
    int _currentLevel;
    bool _evolutionInProgress;
    
    // Random
    std::mt19937 _rng;
    
    // Last responses
    std::string _lastLookResponse;
    
    // Unused but kept for compatibility
};