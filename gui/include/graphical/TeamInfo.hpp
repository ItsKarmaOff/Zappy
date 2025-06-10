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

namespace Gui {

    class TeamInfo {
        public:
            TeamInfo() = default;
            ~TeamInfo() = default;

            ////////////////////////////////////// GETTERS //////////////////////////////////////
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> &getPlayers(void);

            const size_t &getScore(void) const;
            void setScore(size_t score);


        private:
            std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> _players;
            size_t _score;

    };

}

#endif // TEAMINFO_HPP