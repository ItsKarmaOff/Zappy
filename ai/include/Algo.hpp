/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Algo.hpp - Improved Smart Food Search Algorithm
*/

#ifndef ALGO_HPP_
#define ALGO_HPP_

#include "Lib.hpp"
#include <string>
#include <regex>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

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
        // Core survival methods - améliorés
        void smartSurvivalCycle(Player* player);
        void smartFoodSearch(Player* player);
        void normalExploration(Player* player);
        void randomExploration(Player* player);
        bool needsFood() const;
        
        // Nouveau système de ciblage
        void moveToTargetTile(Player* player);
        
        // Response processing
        void waitAndProcessResponses(Player* player, int waitTimeMs);
        void processAllResponses(Player* player);
        void processStructuredResponse(const std::string& response);
        void updateInventory(const std::string& inventoryResponse);
        void analyzeLookResponse(const std::string& lookResponse);
        
        // Parsing utilities - améliorés
        int parseInventoryForFood(const std::string& inventoryResponse);
        std::vector<std::string> parseLookResponse(const std::string& lookResponse);
        bool isFoodNearby(const std::string& lookResponse);
        bool isFoodOnCurrentTile(const std::string& lookResponse);

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
        
        // Nouveaux états pour la recherche intelligente
        int _explorationSteps;
        int _maxExplorationSteps;  
        int _targetTile;           // Après _maxExplorationSteps
        bool _isSearchingFood;     // Après _targetTile
        
        // Générateur de nombres aléatoires
        std::mt19937 _rng;
};

#endif /* !ALGO_HPP_ */