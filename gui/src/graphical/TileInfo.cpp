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
        drawContent(assetsManager);
        models["island"]->draw(
            {_pos.x,
            models["island"]->getAligned(models["island"]->getBoundingBox().min.y) - models["island"]->getDimensions().y,
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

    void TileInfo::drawContent(AssetsManager &assetsManager) const
    {
        auto &models = assetsManager.getModels();

        const float tileRealSize = models["island"]->getDimensions().x;
        const float halfSize = tileRealSize / 2.0f;

        Vector3 basePos = {
            _pos.x - halfSize,
            0.0f,
            _pos.z - halfSize
        };

        int index = 0;
        int itemsPerLine = static_cast<int>(std::floor(tileRealSize));

        for (const auto &[key, nb] : _content) {
            if (nb <= 0) continue;
            for (int i = 0; i < nb; ++i) {
                int offsetX = index % itemsPerLine;
                int offsetZ = index / itemsPerLine;

                float spacing = tileRealSize / static_cast<float>(itemsPerLine);

                Vector3 objPos = {
                    basePos.x + offsetX * spacing + spacing / 2.0f,
                    0.0f,
                    basePos.z + offsetZ * spacing + spacing / 2.0f
                };

                if (models.contains(key)) {
                    float yOffset = models[key]->getAligned(models[key]->getBoundingBox().min.y);
                    Vector3 modelPos = {objPos.x, yOffset, objPos.z};
                    models[key]->draw(modelPos);
                } else {
                    DrawCube({objPos.x, 0.0f, objPos.z}, spacing, spacing, spacing, PURPLE);
                    DrawCubeWires({objPos.x, 0.0f, objPos.z}, spacing, spacing, spacing, BLACK);
                }
                index++;
            }
        }
    }
}