/*
** EPITECH PROJECT, 2025
** TeamInfo.hpp
** File description:
** TeamInfo declaration
*/


#ifndef TEAMINFO_HPP
    #define TEAMINFO_HPP

    #include "PlayerInfo.hpp"
    #include <memory>
    #include <unordered_map>

/**
 * @file TeamInfo.hpp
 * @brief The TeamInfo class for representing team data in the game
 * @author Gianni TUERO
 */

namespace Gui {

    class TeamInfo {
        public:
            TeamInfo();
            ~TeamInfo() = default;

            ////////////////////////////////////// GETTERS //////////////////////////////////////
            /**
             * @brief Gets the players in the team
             * @return Reference to the unordered map of player IDs to PlayerInfo objects
             */
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> &getPlayers(void);

            /**
             * @brief Gets the score of the team
             * @return Constant reference to the team's score
             */
            const size_t &getScore(void) const;
            /**
             * @brief Gets the color associated with the team
             * @return Constant reference to the team's color
             */
            void setScore(size_t score);

            /**
             * @brief Gets the color associated with the team
             * @return Constant reference to the team's color
             */
            const Color &getColor(void) const;
            /**
             * @brief Gets the players in the team
             * @return Reference to the unordered map of player IDs to PlayerInfo objects
             */
            void setColor(Color);


        private:
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> _players; ///< Map of player IDs to PlayerInfo objects
            size_t _score; ///< The score of the team
            Color _color; ///< The color associated with the team

    };



}

#endif // TEAMINFO_HPP