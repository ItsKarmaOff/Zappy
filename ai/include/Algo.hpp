#pragma once
#include "ZappyTypes.hpp"
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <chrono>

class Player;

enum class StrategyPhase {
    EXPLORATION,    // Parcourir la map et collecter tout
    PREPARATION,    // Drop ressources sauf 25 food
    FORK_PHASE,     // Fork toute l'équipe
    INCANTATION,    // Level up en boucle
    CHILD_SPAWNED   // Pour les enfants qui viennent de spawner
};

class Algo {
public:
    Algo();
    ~Algo();
    
    void setPlayer(std::shared_ptr<Player> player);
    void setPlayer(Player* player);
    Player* getPlayer();
    void run();

private:
    // Core strategy
    void executeMainStrategy(Player* player);
    void exploreAndCollect(Player* player);
    void collectResourcesOnCurrentTile(Player* player);
    void forkAllPlayers(Player* player);
    void prepareForIncantations(Player* player);
    void performAllIncantations(Player* player);
    void handleChildSpawned(Player* player);
    
    // Child behavior
    void collectMyFoodShare(Player* player);
    void waitAsChild(Player* player);
    
    // Movement
    void moveForward(Player* player);
    void moveRight(Player* player);
    void moveLeft(Player* player);
    
    // Utilities
    bool hasAllRequiredResources() const;
    bool hasEnoughFood() const;
    void processLookResponse(const std::string& response);
    std::vector<std::string> parseLookResponse(const std::string& lookResponse) const;
    void waitForResponse(Player* player);
    void broadcastResourcesCollected(Player* player);
    
    // Player management
    struct Position {
        int x, y;
        Position(int x = 0, int y = 0) : x(x), y(y) {}
        bool operator==(const Position& other) const { return x == other.x && y == other.y; }
    };

    std::shared_ptr<Player> _player;
    Player* _playerPtr;
    
    // State
    StrategyPhase _currentPhase;
    int _currentLevel;
    int _myFoodCount;
    int _tilesExplored;
    int _emptyTileCount;
    Position _currentPos;
    int _spiralRadius;
    int _spiralSteps;
    int _spiralCurrentSteps;
    int _spiralDirection; // 0=North, 1=East, 2=South, 3=West
    bool _spiralFirstDirection;
    bool _isLeader;
    int _forkedPlayers;
    
    // Resources tracking
    std::map<ResourceType, int> _requiredResources;
    std::map<ResourceType, int> _collectedResources;
    
    // Game state
    std::string _lastLookResponse;
    
    // Movement tracking
    
    
    // Spiral exploration
    
    
    
    
    void initSpiralExploration();
    void moveInSpiral(Player* player);
    void turnToDirection(Player* player, int targetDirection);
    int getCurrentDirection() const;
    
    // Random
    std::mt19937 _rng;
};