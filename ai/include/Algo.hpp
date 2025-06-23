/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo - Survival Algorithm
*/

#ifndef ALGO_HPP_
#define ALGO_HPP_

#include "Lib.hpp"
#include <string>
#include <regex>

class Player;

class Algo {
    public:
        Algo();
        ~Algo();
        void setPlayer(std::shared_ptr<Player> player);
        void setPlayer(Player* player);
        void run();

    protected:
    private:
        // Core survival methods
        void survivalCycle(Player* player);
        void exploreForFood(Player* player);
        bool needsFood() const;
        void searchAndTakeFood(Player* player);
        
        // Response processing
        void waitAndProcessResponses(Player* player, int waitTimeMs);
        void processStructuredResponse(const std::string& response);
        void updateInventory(const std::string& inventoryResponse);
        void analyzeLookResponse(const std::string& lookResponse);
        
        // Parsing utilities
        int parseInventoryForFood(const std::string& inventoryResponse);
        bool isFoodNearby(const std::string& lookResponse);
        bool isFoodOnCurrentTile(const std::string& lookResponse);
        
        // Movement and exploration
        void moveRandomly(Player* player);
        void searchPattern(Player* player);

        // Player references
        std::shared_ptr<Player> _player;
        Player* _playerPtr;
        
        // Survival state
        int _currentFood;
        int _minFoodThreshold;
        int _maxFoodTarget;
        std::string _lastInventoryResponse;
        std::string _lastLookResponse;
        bool _foodNearby;
        bool _foodOnCurrentTile;
        
        // Exploration state
        int _explorationSteps;
        int _maxExplorationSteps;
};

#endif /* !ALGO_HPP_ */