/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Player class implementation
*/
/**
 * @file Player.hpp
 * @brief Player class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */


#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Lib.hpp"
#include "CommandsQueue.hpp"
#include "ZappyTypes.hpp"

class Algo;

/**
 * @class Player
 * @brief Represents a player in the Zappy game with inventory and command management
 */
class Player {
public:
    /**
     * @brief Constructor for Player
     * @param team The team name for this player
     */
    Player(std::string team);
    
    /**
     * @brief Destructor for Player
     */
    ~Player();

    /**
     * @brief Main execution loop for the player
     */
    void run();
    
    /**
     * @brief Broadcast a message to all players
     * @param message The message to broadcast
     */
    void broadcast(const std::string &message);
    
    /**
     * @brief Eject other players from current tile
     */
    void eject();
    
    /**
     * @brief Fork a new player
     */
    void fork();
    
    /**
     * @brief Check current inventory
     */
    void inventory();
    
    /**
     * @brief Look around the current position
     */
    void look();
    
    /**
     * @brief Move forward one tile
     */
    void forward();
    
    /**
     * @brief Turn right 90 degrees
     */
    void right();
    
    /**
     * @brief Turn left 90 degrees
     */
    void left();
    
    /**
     * @brief Get number of available team slots
     */
    void connect_nbr();
    
    /**
     * @brief Take an item from current tile
     * @param item The item name to take
     */
    void take(const std::string &item);
    
    /**
     * @brief Set down an item on current tile
     * @param item The item name to set down
     */
    void set(const std::string &item);
    
    /**
     * @brief Start incantation for level up
     */
    void incantation();

    /**
     * @brief Get the fork player callback function
     * @return The fork callback function
     */
    std::function<void()> getForkPlayerCallback() const { return _forkPlayerCallback; }
    
    /**
     * @brief Check if player is alive
     * @return True if player is alive
     */
    bool isAlive() const { return _alive; }
    
    /**
     * @brief Get the team name
     * @return The team name
     */
    std::string getTeamName() const { return _teamName; }
    
    /**
     * @brief Get the commands queue
     * @return Shared pointer to the commands queue
     */
    std::shared_ptr<CommandsQueue> getCommandsQueue() const { return _commandsQueue; }
    
    /**
     * @brief Get count of specific resource type
     * @param type The resource type to count
     * @return Number of items of that type
     */
    int getItemCount(ResourceType type) const;
    
    /**
     * @brief Get current food count
     * @return Number of food units
     */
    int getFoodCount() const { return getItemCount(ResourceType::FOOD); }
    
    /**
     * @brief Get the complete inventory
     * @return Reference to the inventory map
     */
    const std::map<ResourceType, int>& getInventory() const { return _inventory; }
    
    /**
     * @brief Check if player can evolve to target level
     * @param targetLevel The target level to check
     * @return True if evolution is possible
     */
    bool canEvolveToLevel(int targetLevel) const;
    
    /**
     * @brief Get required items for specific level
     * @param targetLevel The target level
     * @return Map of required resources and quantities
     */
    std::map<ResourceType, int> getRequiredItemsForLevel(int targetLevel) const;
    
    /**
     * @brief Set the commands queue
     * @param queue Shared pointer to the commands queue
     */
    void setCommandsQueue(std::shared_ptr<CommandsQueue> queue) { _commandsQueue = queue; }
    
    /**
     * @brief Set the fork player callback
     * @param callback The callback function for forking
     */
    void setForkPlayerCallback(std::function<void()> callback) { _forkPlayerCallback = callback; }
    
    /**
     * @brief Set player alive status
     * @param alive The alive status
     */
    void setAlive(bool alive) { _alive = alive; }
    
    /**
     * @brief Set communication thread for engine compatibility
     * @param thread The communication thread
     */
    void setCommunicationThread(std::thread&& thread) { _communicationThread = std::move(thread); }
    
    /**
     * @brief Get communication thread reference
     * @return Reference to the communication thread
     */
    std::thread& getCommunicationThread() { return _communicationThread; }
    
    /**
     * @brief Add broadcast message to queue
     * @param broadcast The broadcast message to add
     */
    void addToBroadcastList(const std::string& broadcast) {
        _broadcastQueue.push(broadcast);
        DEBUG << "Added broadcast to queue: [" << broadcast << "] - Queue size now: " << _broadcastQueue.size();
    }
    
    /**
     * @brief Get broadcast messages list
     * @return Reference to broadcast messages vector
     */
    const std::vector<std::string>& getBroadcastMessages() const { return _broadcastMessages; }
    
    /**
     * @brief Process server response
     * @param response The response string from server
     */
    void processResponse(const std::string &response);
    
    /**
     * @brief Get current player level
     * @return The current level
     */
    int getLevel() const { return _level; }
    
    /**
     * @brief Check if there are pending broadcasts
     * @return True if broadcasts are pending
     */
    bool hasPendingBroadcasts() const;
    
    /**
     * @brief Get next broadcast from queue
     * @return The next broadcast message
     */
    std::string getNextBroadcast();

protected:

private:
    int _level = 1; ///< Current player level
    std::string _teamName; ///< Team name
    bool _alive; ///< Player alive status
    std::shared_ptr<CommandsQueue> _commandsQueue; ///< Commands queue for communication
    std::function<void()> _forkPlayerCallback; ///< Callback for forking players
    
    std::map<ResourceType, int> _inventory; ///< Player inventory with resource counts
    std::vector<std::string> _view; ///< Current view of surroundings
    
    std::string _lastTakeCommand; ///< Last take command issued
    bool _waitingForTakeResponse; ///< Flag for pending take response
    
    std::thread _communicationThread; ///< Communication thread for engine compatibility
    std::vector<std::string> _broadcastMessages; ///< Storage for broadcast messages
    std::queue<std::string> _broadcastQueue; ///< Queue for broadcast messages
    
    /**
     * @brief Parse view response from server
     * @param response The view response string
     */
    void parseViewResponse(const std::string &response);
    
    /**
     * @brief Parse inventory response from server
     * @param response The inventory response string
     */
    void parseInventoryResponse(const std::string &response);
    
    /**
     * @brief Add items to inventory
     * @param type The resource type to add
     * @param quantity The quantity to add
     */
    void addToInventory(ResourceType type, int quantity);
    
    /**
     * @brief Handle successful take command
     * @param type The resource type that was taken
     */
    void handleTakeSuccess(ResourceType type);
    
    /**
     * @brief Convert string to resource type
     * @param str The string to convert
     * @return The corresponding resource type
     */
    ResourceType stringToResourceType(const std::string &str) const;
    
    /**
     * @brief Convert resource type to string
     * @param type The resource type to convert
     * @return The corresponding string
     */
    std::string resourceTypeToString(ResourceType type) const;
    
    static const std::map<int, std::map<ResourceType, int>> EVOLUTION_REQUIREMENTS; ///< Evolution requirements table
};

#endif /* !PLAYER_HPP_ */