/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Algo class implementation
*/
/**
 * @file Algo.hpp
 * @brief The Algo class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef ALGO_HPP_
    #define ALGO_HPP_

    #include "ZappyTypes.hpp"

class Player;

/**
 * @enum StrategyPhase
 * @brief Represents the different phases of the AI strategy
 */
enum class StrategyPhase {
    EXPLORATION,    ///< Explore the map and collect all resources
    PREPARATION,    ///< Drop resources except 40 food for survival
    FORK_PHASE,     ///< Fork the entire team
    INCANTATION,    ///< Level up in loop
    CHILD_SPAWNED   ///< For children that just spawned
};

/**
 * @class Algo
 * @brief The main AI algorithm class for the Zappy game with lock file leader election
 */
class Algo {
    public:
        /**
         * @brief Constructor for the Algo class
         */
        Algo();

        /**
         * @brief Destructor for the Algo class
         */
        ~Algo();

        /**
         * @brief Set the player using shared_ptr
         * @param player Shared pointer to the player
         */
        void setPlayer(std::shared_ptr<Player> player);

        /**
         * @brief Set the player using raw pointer
         * @param player Raw pointer to the player
         */
        void setPlayer(Player* player);

        /**
         * @brief Get the current player
         * @return Pointer to the current player
         */
        Player* getPlayer();

        /**
         * @brief Main execution loop for the AI
         */
        void run();

    private:
        /**
         * @brief Try to become the leader by creating a lock file
         * @return True if successfully became leader, false otherwise
         */
        bool tryBecomeLeader();

        /**
         * @brief Clean up lock file when leader terminates
         */
        void cleanup();

        /**
         * @brief Execute the main strategy based on current phase
         * @param player Pointer to the player
         */
        void executeMainStrategy(Player* player);

        /**
         * @brief Explore the map and collect resources
         * @param player Pointer to the player
         */
        void exploreAndCollect(Player* player);

        /**
         * @brief Collect resources on the current tile
         * @param player Pointer to the player
         */
        void collectResourcesOnCurrentTile(Player* player);

        /**
         * @brief Fork all players for the team
         * @param player Pointer to the player
         */
        void forkAllPlayers(Player* player);

        /**
         * @brief Prepare for incantations by dropping resources
         * @param player Pointer to the player
         */
        void prepareForIncantations(Player* player);

        /**
         * @brief Perform all incantations to level up
         * @param player Pointer to the player
         */
        void performAllIncantations(Player* player);

        /**
         * @brief Handle behavior for spawned children
         * @param player Pointer to the player
         */
        void handleChildSpawned(Player* player);

        /**
         * @brief Collect food share for child players
         * @param player Pointer to the player
         */
        void collectMyFoodShare(Player* player);

        /**
         * @brief Wait behavior for child players
         * @param player Pointer to the player
         */
        void waitAsChild(Player* player);

        /**
         * @brief Move forward one tile
         * @param player Pointer to the player
         */
        void moveForward(Player* player);

        /**
         * @brief Turn right 90 degrees
         * @param player Pointer to the player
         */
        void moveRight(Player* player);

        /**
         * @brief Turn left 90 degrees
         * @param player Pointer to the player
         */
        void moveLeft(Player* player);

        /**
         * @brief Check if all required resources are collected
         * @return True if all resources are available
         */
        bool hasAllRequiredResources() const;

        /**
         * @brief Check if there is enough food
         * @return True if enough food is available
         */
        bool hasEnoughFood() const;

        /**
         * @brief Process the response from look command
         * @param response The look command response
         */
        void processLookResponse(const std::string& response);

        /**
         * @brief Parse the look response into tiles
         * @param lookResponse The look command response string
         * @return Vector of tile contents
         */
        std::vector<std::string> parseLookResponse(const std::string& lookResponse) const;

        /**
         * @brief Wait for server response
         * @param player Pointer to the player
         */
        void waitForResponse(Player* player);

        /**
         * @brief Broadcast that resources are collected
         * @param player Pointer to the player
         */
        void broadcastResourcesCollected(Player* player);

        /**
         * @brief Broadcast that mission is complete (level 8 reached)
         * @param player Pointer to the player
         */
        void broadcastMissionComplete(Player* player);

        /**
         * @struct Position
         * @brief Represents a position on the map
         */
        struct Position {
            int x, y; ///< X and Y coordinates

            /**
             * @brief Constructor for Position
             * @param x X coordinate (default: 0)
             * @param y Y coordinate (default: 0)
             */
            Position(int x = 0, int y = 0) : x(x), y(y) {}

            /**
             * @brief Equality operator for positions
             * @param other Other position to compare
             * @return True if positions are equal
             */
            bool operator==(const Position& other) const { return x == other.x && y == other.y; }
        };

        std::shared_ptr<Player> _player; ///< Shared pointer to player
        Player* _playerPtr; ///< Raw pointer to player

        StrategyPhase _currentPhase; ///< Current strategy phase
        int _currentLevel; ///< Current player level
        int _myFoodCount; ///< Current food count
        int _tilesExplored; ///< Number of tiles explored
        int _emptyTileCount; ///< Number of empty tiles found
        Position _currentPos; ///< Current position on map
        int _spiralRadius; ///< Current spiral exploration radius
        int _spiralSteps; ///< Steps in current spiral direction
        int _spiralCurrentSteps; ///< Current step count in direction
        int _spiralDirection; ///< Current direction (0=North, 1=East, 2=South, 3=West)
        bool _spiralFirstDirection; ///< Flag for spiral direction tracking
        bool _isLeader; ///< True if this is the leader player
        int _forkedPlayers; ///< Number of players forked

        std::map<ResourceType, int> _requiredResources; ///< Required resources for all levels
        std::map<ResourceType, int> _collectedResources; ///< Currently collected resources

        std::string _lastLookResponse; ///< Last look command response

        /**
         * @brief Initialize spiral exploration pattern
         */
        void initSpiralExploration();

        /**
         * @brief Move in spiral pattern
         * @param player Pointer to the player
         */
        void moveInSpiral(Player* player);

        /**
         * @brief Turn to specified direction
         * @param player Pointer to the player
         * @param targetDirection Target direction to face
         */
        void turnToDirection(Player* player, int targetDirection);

        /**
         * @brief Get current facing direction
         * @return Current direction (0-3)
         */
        int getCurrentDirection() const;

        /**
         * @brief kill all the children
         */
        void killAllChildren();

        std::mt19937 _rng; ///< Random number generator
};

#endif /* ALGO_HPP_ */
