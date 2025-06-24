/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Player.hpp - Improved with proper resource management
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <thread>
#include "CommandsQueue.hpp"
#include "ZappyTypes.hpp"

class Player {
public:
    Player(std::string team);
    ~Player();

    // Actions de base
    void run();
    void broadcast(const std::string &message);
    void eject();
    void fork();
    void inventory();
    void look();
    void forward();
    void right();
    void left();
    void connect_nbr();
    void take(const std::string &item);
    void set(const std::string &item);
    void incantation();

    // Getters
    bool isAlive() const { return _alive; }
    std::string getTeamName() const { return _teamName; }
    std::shared_ptr<CommandsQueue> getCommandsQueue() const { return _commandsQueue; }
    
    // Gestion inventaire améliorée
    int getItemCount(ResourceType type) const;
    int getFoodCount() const { return getItemCount(ResourceType::FOOD); }
    const std::map<ResourceType, int>& getInventory() const { return _inventory; }
    
    // Vérifications pour l'évolution
    bool canEvolveToLevel(int targetLevel) const;
    std::map<ResourceType, int> getRequiredItemsForLevel(int targetLevel) const;
    
    // Setters
    void setCommandsQueue(std::shared_ptr<CommandsQueue> queue) { _commandsQueue = queue; }
    void setForkPlayerCallback(std::function<void()> callback) { _forkPlayerCallback = callback; }
    void setAlive(bool alive) { _alive = alive; }
    
    // Communication thread management (for Engine compatibility)
    void setCommunicationThread(std::thread&& thread) { _communicationThread = std::move(thread); }
    std::thread& getCommunicationThread() { return _communicationThread; }
    
    // Broadcast management (for Engine compatibility)
    void addToBroadcastList(const std::string& message) { 
        _broadcastMessages.push_back(message); 
        DEBUG << "Received broadcast: " << message;
    }
    const std::vector<std::string>& getBroadcastMessages() const { return _broadcastMessages; }

    // Processing
    void processResponse(const std::string &response);
    int getLevel() const { return _level; }

private:
    // Variables membres
    int _level = 1;
    std::string _teamName;
    bool _alive;
    std::shared_ptr<CommandsQueue> _commandsQueue;
    std::function<void()> _forkPlayerCallback;
    
    // Inventaire avec types stricts
    std::map<ResourceType, int> _inventory;
    
    // Vue actuelle
    std::vector<std::string> _view;
    
    // État des commandes en cours
    std::string _lastTakeCommand;
    bool _waitingForTakeResponse;
    
    // Communication thread (for Engine compatibility)
    std::thread _communicationThread;
    
    // Broadcast messages storage
    std::vector<std::string> _broadcastMessages;

    // Méthodes utilitaires
    void parseViewResponse(const std::string &response);
    void parseInventoryResponse(const std::string &response);
    void addToInventory(ResourceType type, int quantity);
    void handleTakeSuccess(ResourceType type);
    
    // Conversion string <-> ResourceType
    ResourceType stringToResourceType(const std::string &str) const;
    std::string resourceTypeToString(ResourceType type) const;
    
    // Tables de correspondance pour l'évolution
    static const std::map<int, std::map<ResourceType, int>> EVOLUTION_REQUIREMENTS;
};