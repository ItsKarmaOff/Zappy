/*
** EPITECH PROJECT, 2025
** GameInfo.cpp
** File description:
** GameInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "GameInfo.hpp"
#include "Lib.hpp"
#include <raylib.h>

namespace Gui {
    GameInfo::GameInfo()
    : _camera(), _mapSize({3, 3})
    {
        _camera.position = {10.0f, 10.0f, 10.0f};
        _camera.target = {0, 0, 0};
        _camera.up = {0, 1.0, 0};
        _camera.projection = CAMERA_PERSPECTIVE;
        _camera.fovy = 60.0f;
        _tiles = {};
        _teams = {};
        _players = {};
    }

    Camera3D& GameInfo::getCamera()
    {
        return _camera;
    }

    Vector2& GameInfo::getMapSize()
    {
        return _mapSize;
    }


    std::unordered_map<Vector2, TileInfo> &GameInfo::getTiles()
    {
        return _tiles;
    }

    std::unordered_map<std::string, TeamInfo> &GameInfo::getTeams(void)
    {
        return _teams;
    }

    std::unordered_map<size_t, std::shared_ptr<PlayerInfo>> &GameInfo::getPlayers()
    {
        return _players;
    }

}