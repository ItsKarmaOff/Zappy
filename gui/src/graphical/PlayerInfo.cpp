/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The PlayerInfo class implementation
*/
/**
 * @file PlayerInfo.cpp
 * @brief The PlayerInfo class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "PlayerInfo.hpp"

namespace Gui {
    PlayerInfo::PlayerInfo(std::string teamName_) :
    _isSelected(false), _modelPos()
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

    const Color &PlayerInfo::getColor(void) const
    {
        return _teamColor;
    }

    void PlayerInfo::setColor(Color col)
    {
        _teamColor = col;
    }

    const std::string &PlayerInfo::getTeamName(void) const
    {
        return _teamName;
    }

    void PlayerInfo::setTeamName(std::string name_)
    {
        _teamName = name_;
    }

    bool &PlayerInfo::isIncanting(void)
    {
        return _isIncanting;
    }
    const bool &PlayerInfo::isIncanting(void) const
    {
        return _isIncanting;
    }
    void PlayerInfo::setIncanting(bool incanting)
    {
        _isIncanting = incanting;
    }

    ////////////////////////////////////// FOR CLICKING ON PLAYER //////////////////////////////////////
    const bool &PlayerInfo::isSelected(void) const
    {
        return _isSelected;
    }

    bool &PlayerInfo::isSelected(void)
    {
        return _isSelected;
    }

    void PlayerInfo::setSelected(bool selected)
    {
        _isSelected = selected;
    }

    ////////////////////////////////////// Model Methods //////////////////////////////////////

    const Vector3 &PlayerInfo::getModelPos(void) const
    {
        return _modelPos;
    }

    void PlayerInfo::setModelPos(const Vector3 &pos)
    {
        _modelPos = pos;
    }

    const Matrix &PlayerInfo::getModelTransform(void) const
    {
        return _modelTransform;
    }
}