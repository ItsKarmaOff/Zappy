/*
** EPITECH PROJECT, 2025
** TileInfo.cpp
** File description:
** TileInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "TileInfo.hpp"
#include "Graphics.hpp"
#include "Logs.hpp"

namespace Gui {
    TileInfo::TileInfo(const Vector3 &pos)
    {
        _pos = pos;
        // food, linemate, deraumere, sibur, mendiane, phiras, thystame
        _content = {
            {"food", 0},
            {"linemate", 0},
            {"deraumere", 0},
            {"sibur", 0},
            {"mendiane", 0},
            {"phiras", 0},
            {"thystame", 0}
        };
    }

    TileInfo::TileInfo()
    {
        _pos = {0, 0, 0};
    }


    const Vector3& TileInfo::getPos() const
    {
        return _pos;
    }

    void TileInfo::setPos(const Vector3 &pos)
    {
        _pos = pos;
    }

    std::unordered_map<std::string, int>& TileInfo::getContent(void)
    {
        return _content;
    }

    void TileInfo::setPos(const std::unordered_map<std::string, int> &cont)
    {
        _content = cont;
    }


    void TileInfo::draw(std::unordered_map<std::string, Model> &models)
    {
        DrawCube({_pos.x, -5, _pos.y}, TILE_SIZE, 1.0f, TILE_SIZE, SKYBLUE);
        DrawCubeWires({_pos.x, -5, _pos.y}, TILE_SIZE, 1.0f, TILE_SIZE, BLACK);
        if (_content["food"] > 0) {
            DrawModel(models["food"], {_pos.x, 2, _pos.z}, 0.3f, WHITE);
        }
        DrawModel(models["linemate"], {_pos.x, 2, _pos.z}, 15.0f, WHITE);
        DrawModel(models["island"], {_pos.x, 1, _pos.z}, 0.5f, WHITE);
    }
}