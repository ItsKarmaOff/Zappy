/*
** EPITECH PROJECT, 2025
** PlayerInfo.cpp
** File description:
** PlayerInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "PlayerInfo.hpp"

namespace Gui {
    const PlayerInfo::Orientation& PlayerInfo::getOrientation() const
    {
        return _orientation;
    }

    void PlayerInfo::setOrientation(Orientation orientation)
    {
        _orientation = orientation;
    }
    void PlayerInfo::setOrientation(int orientation)
    {
        _orientation = static_cast<Orientation>(orientation);
    }

    const size_t& PlayerInfo::getLevel() const
    {
        return _level;
    }

    void PlayerInfo::setLevel(size_t level)
    {
        _level = level;
    }

    const Vector2& PlayerInfo::getPos() const
    {
        return _pos;
    }

    void PlayerInfo::setPos(Vector2 pos)
    {
        _pos = pos;
    }


}