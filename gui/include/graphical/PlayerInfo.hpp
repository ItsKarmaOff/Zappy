/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The PlayerInfo class declaration
*/
/**
 * @file PlayerInfo.hpp
 * @brief The PlayerInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef PLAYERINFO_HPP
    #define PLAYERINFO_HPP

    #include "Lib.hpp"
    #include <raylib.h>

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
                NORTH = 1,  ///< Player facing north
                EAST,       ///< Player facing east
                SOUTH,      ///< Player facing south
                WEST,       ///< Player facing west
            };

            /**
             * @enum ResourceType
             * @brief The ResourceType enum represents the types of resources a player can have in their inventory.
             */
            enum ResourceType {
                FOOD,       ///< Food resource
                LINEMATE,   ///< Linemate resource
                DERAUMERE,  ///< Deraumere resource
                SIBUR,      ///< Sibur resource
                MENDIANE,   ///< Mendiane resource
                PHIRAS,     ///< Phiras resource
                THYSTAME    ///< Thystame resource
            };

            /**
             * @enum PlayerState
             * @brief Represents the current state or action of a player
             */
            enum PlayerState {
                IDLE,         ///< Player is idle/normal state
                INCANTATION,  ///< Player is performing an incantation
                EXPELLED,     ///< Player has been expelled
                EGG,         ///< Player is an egg
            };



            /////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Construct a new PlayerInfo object with default values.
             */
            PlayerInfo() = default;

            /**
             * @brief Construct a new PlayerInfo object with specified team name
             * @param teamName_ The name of the team the player belongs to
             */
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
             * @brief Get the current state of the player
             * @return Constant reference to the player's state
             */
            const PlayerState &getState(void) const;

            /**
             * @brief Get the color associated with the player's team
             * @return Constant reference to the color
             */
            const Color &getColor(void) const;

            /**
             * @brief Get the name of the team the player belongs to
             * @return Constant reference to the team name
             */
            const std::string &getTeamName(void) const;

            /**
             * @brief Check if the player is currently selected by the user
             * @return Constant reference to the selection state boolean
             */
            const bool &isSelected(void) const;

            /**
             * @brief Get mutable reference to the player's selection state
             * @return Reference to the selection state boolean
             */
            bool &isSelected(void);

            /**
             * @brief Check if the player is currently performing an incantation
             * @return Constant reference to the incantation state boolean
             */
            const bool &isIncanting(void) const;

            /**
             * @brief Get mutable reference to the player's incantation state
             * @return Reference to the incantation state boolean
             */
            bool &isIncanting(void);



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
             * @brief Set the state of the player
             * @param state The state to set
             */
            void setState(PlayerState state);

            /**
             * @brief Set the color associated with the player's team
             * @param color The color to set
             */
            void setColor(Color color);

            /**
             * @brief Set the name of the team the player belongs to
             * @param teamName_ The team name to set
             */
            void setTeamName(std::string teamName_);

            /**
             * @brief Set whether the player is selected by the user
             * @param selected Boolean indicating if the player is selected
             */
            void setSelected(bool selected);

            /**
             * @brief Set whether the player is performing an incantation
             * @param incanting Boolean indicating if the player is incanting
             */
            void setIncanting(bool incanting);



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



            //////////////// Model Methods /////////////////////////////////////

            /**
             * @brief Get the 3D position of the player's model
             * @return Constant reference to the model position Vector3
             */
            const Vector3 &getModelPos(void) const;

            /**
             * @brief Set the 3D position of the player's model
             * @param pos The position to set
             */
            void setModelPos(const Vector3 &pos);

            /**
             * @brief Get the transformation matrix for the player's model
             * @return Constant reference to the transformation matrix
             */
            const Matrix &getModelTransform(void) const;

            /**
             * @brief Set the transformation matrix for the player's model
             * @param transform The transformation matrix to set
             */
            void setModelTransform(const Matrix &transform);



        private:

            //////////////// Private Attributes ////////////////////////////////

            Color _teamColor;                              ///< Color associated with the player's team
            Orientation _orientation;                      ///< The orientation of the player
            PlayerState _state;                            ///< The current state of the player
            size_t _level;                                 ///< The level of the player
            Vector2 _pos;                                  ///< The position of the player on the game map
            std::map<ResourceType, size_t> _inventory;     ///< The inventory of the player
            std::string _teamName;                         ///< The name of the team the player belongs to

            bool _isSelected;                              ///< Whether the player is currently selected by the user
            Vector3 _modelPos;                             ///< Position of the model in 3D space, used for drawing
            Matrix _modelTransform;                        ///< Transformation matrix for the model
            bool _isIncanting = false;                     ///< Whether the player is currently performing an incantation
    };



    /**
     * @brief Mapping from resource types to their string representations
     */
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