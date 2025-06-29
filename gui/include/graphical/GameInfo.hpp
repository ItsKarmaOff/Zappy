/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The GameInfo class declaration
*/
/**
 * @file GameInfo.hpp
 * @brief The GameInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef GAMEINFO_HPP
    #define GAMEINFO_HPP

    #include "TileInfo.hpp"
    #include "TeamInfo.hpp"


// TODO: pk dans std ??
// Hash function specialization for Vector2
namespace std {
    template<>
    struct hash<Vector2> {
        std::size_t operator()(const Vector2& v) const {
            return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1);
        }
    };
}

namespace Gui {
    /**
     * @class GameInfo
     * @brief Manages and stores game state information including camera, map, tiles, teams, and players
     */
    class GameInfo {
        public:

            /**
             * @brief Default constructor
             * Initializes camera and map size with default values
             */
            GameInfo();

            /**
             * @brief Default destructor
             */
            ~GameInfo() = default;

            /**
             * @brief Gets the reference to the game's camera
             * @return Reference to the 3D camera used in the game
             */
            Camera3D &getCamera();

            /**
             * @brief Gets the reference to the map size
             * @return Reference to the Vector2 containing map dimensions
             */
            Vector2 &getMapSize();

            /**
             * @brief Gets the reference to the tiles collection
             * @return Reference to the map of tile information indexed by position
             */
            std::unordered_map<Vector2, TileInfo> &getTiles();

            /**
             * @brief Gets the reference to the teams collection
             * @return Reference to the map of team information indexed by team name
             */
            std::unordered_map<std::string, TeamInfo> &getTeams(void);

            /**
             * @brief Gets the reference to the players collection
             * @return Reference to the map of player information indexed by player ID
             */
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> &getPlayers();



        private:


            //////////////// Private Attributes ////////////////////////////////

            Camera3D _camera; ///< 3D camera used for rendering the game world
            Vector2 _mapSize; ///< Dimensions of the game map
            std::unordered_map<Vector2, TileInfo> _tiles; ///< Collection of tiles indexed by position
            std::unordered_map<std::string, TeamInfo> _teams; ///< Collection of teams indexed by team name
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> _players; ///< Collection of players indexed by ID
    };
}

#endif // GAMEINFO_HPP