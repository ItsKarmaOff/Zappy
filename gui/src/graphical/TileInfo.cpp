/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The TileInfo class implementation
*/
/**
 * @file TileInfo.cpp
 * @brief The TileInfo class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "TileInfo.hpp"

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

        /*                 static float deg = 0.0f;
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

        int gridIndex = 0;
        int itemsPerLine = static_cast<int>(std::floor(tileRealSize / 1.0f));
        // Hauteur verticale pour empiler les objets
        const float stackHeight = 0.5f;
        // Nombre maximum d'objets à empiler dans une pile
        const int maxStackSize = 15;


        for (const auto &[key, nb] : _content) {
            if (nb <= 0) continue;
            int offsetX = gridIndex % itemsPerLine;
            int offsetZ = gridIndex / itemsPerLine;
            float spacing = tileRealSize / static_cast<float>(itemsPerLine);
            Vector3 baseObjPos = {
                basePos.x + offsetX * spacing + spacing / 2.0f,
                0.0f,
                basePos.z + offsetZ * spacing + spacing / 2.0f
            };
            // Nombre de piles nécessaires
            int numStacks = (nb + maxStackSize - 1) / maxStackSize;

            for (int stack = 0; stack < numStacks; stack++) {
                float stackOffsetX = stack % 2 * (spacing * 0.4f);
                float stackOffsetZ = (stack / 2) * (spacing * 0.4f);
                int itemsInThisStack = std::min(maxStackSize, nb - stack * maxStackSize);
                for (int i = 0; i < itemsInThisStack; i++) {
                    if (models.contains(key)) {
                        float yOffset = models[key]->getAligned(models[key]->getBoundingBox().min.y);
                        Vector3 modelPos = {
                            baseObjPos.x + stackOffsetX - (spacing * 0.2f),
                            yOffset + (i * stackHeight),
                            baseObjPos.z + stackOffsetZ - (spacing * 0.2f)
                        };
                        float floatOffset = models[key]->getFloatingOffset();
                        Vector3 floatingPos = {modelPos.x, modelPos.y + floatOffset, modelPos.z};
                        models[key]->applyRotationEffect(0.0f, 0.5f + (i * 0.2f));  // Vitesse variable selon la hauteur
                        models[key]->draw(floatingPos);
                    } else {
                        DrawCube({
                            baseObjPos.x + stackOffsetX,
                            stackHeight * i,
                            baseObjPos.z + stackOffsetZ
                        }, spacing * 0.6f, spacing * 0.6f, spacing * 0.6f, PURPLE);
                        DrawCubeWires({
                            baseObjPos.x + stackOffsetX,
                            stackHeight * i,
                            baseObjPos.z + stackOffsetZ
                        }, spacing * 0.6f, spacing * 0.6f, spacing * 0.6f, BLACK);
                    }
                }
            }
            gridIndex++;
        }
    }
}
