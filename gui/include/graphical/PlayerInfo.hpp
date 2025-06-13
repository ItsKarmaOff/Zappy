/*
** EPITECH PROJECT, 2025
** PlayerInfo.hpp
** File description:
** PlayerInfo declaration
*/


#ifndef PLAYERINFO_HPP
    #define PLAYERINFO_HPP
#include <chrono>
#include <cstddef>
#include <map>
#include <queue>
#include <raylib.h>
#include <string>



namespace Gui
{
    /**
     * @class PlayerInfo
     * @brief The PlayerInfo class represents a player in the game with position, orientation, level and inventory.
     */
    class PlayerInfo {
        public:
            /////////////// Enumerations //////////////////////////////////////

            /**
             * @enum Orientation
             * @brief The Orientation enum represents the orientation of a player.
             */
            enum Orientation {
                NORTH = 1,
                EAST,
                SOUTH,
                WEST,
            };

            /**
             * @enum ResourceType
             * @brief The ResourceType enum represents the types of resources a player can have in their inventory.
             */
            enum ResourceType {
                FOOD,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };

            enum PlayerState {
                IDLE,
                INCANTATION,
                EXPELLED,
            };

            /////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Construct a new PlayerInfo object with default values.
             */
            PlayerInfo() = default;
            PlayerInfo(std::string teamName_);

            /**
             * @brief Destroy the PlayerInfo object.
             */
            ~PlayerInfo() = default;



            //////////////// Getters ///////////////////////////////////////////

            /**
             * @brief Get the orientation of the player.
             * @return The orientation of the player
             */
            const Orientation &getOrientation() const;

            /**
             * @brief Get the level of the player.
             * @return The level of the player
             */
            const size_t &getLevel() const;

            /**
             * @brief Get the position of the player (tile position).
             * @return The position of the player
             */
            const Vector2 &getPos() const;

            /**
             * @brief Get the inventory of the player.
             * @return The inventory of the player
             */
            const std::map<ResourceType, size_t> &getInventory() const;

            /**
             * @brief Get the State object
             *
             * @return const PlayerState&
             */
            const PlayerState &getState(void) const;


            std::queue<std::string> &getMessagesToBroadcast(void);

            const Color &getColor(void) const;

            std::chrono::steady_clock::time_point &getClock(void);

            const bool &isBroadcasting(void) const;

            const std::string &getTeamName(void) const;

            const bool &isSelected(void) const;
            bool &isSelected(void);



            //////////////// Setters ///////////////////////////////////////////

            /**
             * @brief Set the orientation of the player.
             * @param orientation The orientation to set
             */
            void setOrientation(Orientation orientation);

            /**
             * @brief Set the orientation of the player using an integer value.
             * @param orientation The integer value representing the orientation
             */
            void setOrientation(int orientation);


            /**
             * @brief Set the level of the player.
             * @param level The level to set
             */
            void setLevel(size_t level);

            /**
             * @brief Set the position of the player.
             * @param pos The position to set
             */
            void setPos(Vector2 pos);

            /**
             * @brief Set the inventory of the player.
             * @param inventory The inventory to set
             */
            void setInventory(const std::map<ResourceType, size_t> &inventory);

            /**
             * @brief Set the State object
             * @param state The state to set
             */
            void setState(PlayerState state);


            void setColor(Color color);

            void setBroadcasting(bool broadcasting);

            void setTeamName(std::string teamName_);

            void setSelected(bool selected);





            //////////////// Inventory Management Methods //////////////////////

            /**
             * @brief Add a resource to the player's inventory.
             * @param type The type of resource to add
             * @param quantity The quantity of the resource to add
             */
            void addResource(ResourceType type, size_t quantity);

            /**
             * @brief Remove a resource from the player's inventory.
             * @param type The type of resource to remove
             * @param quantity The quantity of the resource to remove
             */
            void removeResource(ResourceType type, size_t quantity);


            ////////////////////////////////////// Model Methods //////////////////////////////////////
            const Vector3 &getModelPos(void) const;
            void setModelPos(const Vector3 &pos);

            const Matrix &getModelTransform(void) const;
            void setModelTransform(const Matrix &transform);
        private:

            //////////////// Private Attributes ////////////////////////////////
            Color _teamColor;
            Orientation _orientation;   // The orientation of the player
            PlayerState _state;   // The orientation of the player
            size_t _level;  // The level of the player
            Vector2 _pos;   // The position of the player
            std::map<ResourceType, size_t> _inventory;  // The inventory of the player
            std::queue<std::string> _messagesToBroadcast;
            std::chrono::steady_clock::time_point _clock;
            bool _broadcast;
            std::string _teamName;

            bool _isSelected;
            Vector3 _modelPos; // Position of the model in 3D space, used for drawing
            Matrix _modelTransform; // Transformation matrix for the model
    };

    static const std::map<PlayerInfo::ResourceType, std::string> ResourceToString = {
        {PlayerInfo::ResourceType::FOOD, "food"},
        {PlayerInfo::ResourceType::LINEMATE, "linemate"},
        {PlayerInfo::ResourceType::DERAUMERE, "deraumere"},
        {PlayerInfo::ResourceType::SIBUR, "sibur"},
        {PlayerInfo::ResourceType::MENDIANE, "mendiane"},
        {PlayerInfo::ResourceType::PHIRAS, "phiras"},
        {PlayerInfo::ResourceType::THYSTAME, "thystame"}
    };
}

#endif // PLAYERINFO_HPP