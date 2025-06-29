/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The TeamInfo class implementation
*/
/**
 * @file TeamInfo.cpp
 * @brief The TeamInfo class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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