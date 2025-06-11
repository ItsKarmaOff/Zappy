/*
** EPITECH PROJECT, 2025
** TileInfo.cpp
** File description:
** TileInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "TileInfo.hpp"
#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Lib.hpp"
#include "Logs.hpp"
#include <chrono>
#include <raymath.h>

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

    std::map<std::string, int>& TileInfo::getContent(void)
    {
        return _content;
    }

    void TileInfo::setContent(const std::map<std::string, int> &cont)
    {
        _content = cont;
    }


    void TileInfo::draw(AssetsManager &assetsManager)
    {
        auto &models = assetsManager.getModels();
        float startX = _pos.x - TILE_SIZE / 2.0f;
        float startZ = _pos.z - TILE_SIZE / 2.0f;

        int index = 0;
        int itemsPerLine = TILE_SIZE;

        for (auto &[key, nb] : _content) {
            if (nb <= 0) continue;

            int offsetX = index % itemsPerLine;
            int offsetZ = index / itemsPerLine;

            Vector3 objPos = {
                startX + offsetX + 0.5f,
                0.0f,
                startZ + offsetZ + 0.5f
            };
            if (models.contains(key)) {
                // need to redo the origin of the model
                models[key]->draw({
                    objPos.x, 3.0
                    /* models[key]->getDimensions().y / 2.0f */,
                    objPos.z}
                );
            } else {
                DrawCube({objPos.x, 0.0f, objPos.z}, 1.0f, 1.0f, 1.0f, PURPLE);
                DrawCubeWires({objPos.x, 0.0f, objPos.z}, 1.0f, 1.0f, 1.0f, BLACK);
            }
            index++;
        }
        models["island"]->draw(
            {_pos.x,
            -assetsManager.getModels().at("island")->getHeight() / 2.0f,
            _pos.z},
            WHITE
        );
        // à fix
        /*
        static float deg = 0.0f;
        static std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
        if (Lib::delay(50, lastTime)) {
            deg += 1.0f;
            deg = fmod(deg, 360.0f);
            float offset = sinf(DEG2RAD * deg) * 0.2f;
            models["food"].transform = MatrixTranslate(0.0f, offset, 0.0f);
            models["linemate"].transform = MatrixTranslate(0.0f, offset, 0.0f);
        } */
    }
}