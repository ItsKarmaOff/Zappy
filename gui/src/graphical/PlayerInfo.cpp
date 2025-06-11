/*
** EPITECH PROJECT, 2025
** PlayerInfo.cpp
** File description:
** PlayerInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "PlayerInfo.hpp"
#include <string>

namespace Gui {
    PlayerInfo::PlayerInfo(std::string teamName_)
    {
        _teamName = teamName_;
    }

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

    const std::map<PlayerInfo::ResourceType, size_t>& PlayerInfo::getInventory() const
    {
        return _inventory;
    }

    void PlayerInfo::setInventory(const std::map<PlayerInfo::ResourceType, size_t> &inventory)
    {
        _inventory = inventory;
    }

    const PlayerInfo::PlayerState &PlayerInfo::getState(void) const
    {
        return _state;
    }

    void PlayerInfo::setState(PlayerState state)
    {
        _state = state;
    }


    void PlayerInfo::addResource(ResourceType type, size_t quantity)
    {
        _inventory[type] += quantity;
    }

    void PlayerInfo::removeResource(ResourceType type, size_t quantity)
    {
        if (_inventory[type] >= quantity)
            _inventory[type] -= quantity;
        else
            _inventory[type] = 0;
    }

    std::queue<std::string> &PlayerInfo::getMessagesToBroadcast(void)
    {
        return _messagesToBroadcast;
    }

    const Color &PlayerInfo::getColor(void) const
    {
        return _teamColor;
    }

    void PlayerInfo::setColor(Color col)
    {
        _teamColor = col;
    }

    std::chrono::steady_clock::time_point &PlayerInfo::getClock(void)
    {
        return _clock;
    }

    const bool &PlayerInfo::isBroadcasting(void) const
    {
        return _broadcast;
    }

    void PlayerInfo::setBroadcasting(bool broadcasting)
    {
        _broadcast = broadcasting;
    }

    const std::string &PlayerInfo::getTeamName(void) const
    {
        return _teamName;
    }

    void PlayerInfo::setTeamName(std::string name_)
    {
        _teamName = name_;
    }

}