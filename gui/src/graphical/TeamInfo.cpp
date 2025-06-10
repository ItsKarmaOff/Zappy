/*
** EPITECH PROJECT, 2025
** TeamInfo.cpp
** File description:
** TeamInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "TeamInfo.hpp"

namespace Gui {
    TeamInfo::TeamInfo()
    {
        _color = WHITE;
    }
    
    std::unordered_map<size_t, std::shared_ptr<PlayerInfo>>& TeamInfo::getPlayers(void)
    {
        return _players;
    }

    const size_t& TeamInfo::getScore(void) const
    {
        return _score;
    }

    void TeamInfo::setScore(size_t score)
    {
        _score = score;
    }

    const Color& TeamInfo::getColor(void) const
    {
        return _color;
    }

    void TeamInfo::setColor(Color rgb)
    {
        _color = rgb;
    }
}