/*
** EPITECH PROJECT, 2025
** AssetsManager.cpp
** File description:
** AssetsManager in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "AssetsManager.hpp"
#include "Graphics.hpp"
#include "Logs.hpp"
#include "ModelInfo.hpp"
#include <memory>
#include <raylib.h>
#include <tuple>

namespace Gui {
    AssetsManager::~AssetsManager()
    {
        unloadAssets();
    }
    void AssetsManager::loadAssets()
    {
        /* food */
        _models["food"] = std::make_shared<ModelInfo>("gui/assets/food.glb");
        _models["food"]->setScale(_models["food"]->scaleToSize(1.0f));


        /* linemate */
        _models["linemate"] = std::make_shared<ModelInfo>("gui/assets/linemate.glb");
        _models["linemate"]->setScale(_models["linemate"]->scaleToSize(1.0f));

        /* deraumere */
        _models["deraumere"] = std::make_shared<ModelInfo>("gui/assets/deraumere.glb");
        _models["deraumere"]->setScale(_models["deraumere"]->scaleToSize(1.0f));

        /* sibur */
        _models["sibur"] = std::make_shared<ModelInfo>("gui/assets/sibur.glb");
        _models["sibur"]->setScale(_models["sibur"]->scaleToSize(1.0f));

        /* mendiane */
        _models["mendiane"] = std::make_shared<ModelInfo>("gui/assets/mendiane.glb");
        _models["mendiane"]->setScale(_models["mendiane"]->scaleToSize(1.0f));

        /* phiras */
        _models["phiras"] = std::make_shared<ModelInfo>("gui/assets/phiras.glb");
        _models["phiras"]->setScale(_models["phiras"]->scaleToSize(1.0f));

        /* thystame */
        _models["thystame"] = std::make_shared<ModelInfo>("gui/assets/thystame.glb");
        _models["thystame"]->setScale(_models["thystame"]->scaleToSize(1.0f));

        /* island */
        _models["island"] = std::make_shared<ModelInfo>("gui/assets/tile.glb", 1.0f);
        _models["island"]->setScale(_models["island"]->scaleToSize(TILE_SIZE - 0.5));

        /* player */
        _models["player0"] = std::make_shared<ModelInfo>("gui/assets/egg.glb");

        _models["player1"] = std::make_shared<ModelInfo>("gui/assets/player1.glb");
        _models["player1"]->setScale(_models["player1"]->scaleToSize(4.0f));

        _models["player2"] = std::make_shared<ModelInfo>("gui/assets/player2.glb");
        _models["player2"]->setScale(_models["player2"]->scaleToSize(3.0f));

        _models["player3"] = std::make_shared<ModelInfo>("gui/assets/player3.glb");
        _models["player3"]->setScale(_models["player3"]->scaleToSize(2.0f));

        _models["player4"] = std::make_shared<ModelInfo>("gui/assets/player4.glb");
        _models["player4"]->setScale(_models["player4"]->scaleToSize(2.0f));

        _models["player5"] = std::make_shared<ModelInfo>("gui/assets/player5.glb");
        _models["player5"]->setScale(_models["player5"]->scaleToSize(2.0f));

        _models["player6"] = std::make_shared<ModelInfo>("gui/assets/player6.glb");
        _models["player6"]->setScale(_models["player6"]->scaleToSize(3.0f));

        _models["player7"] = std::make_shared<ModelInfo>("gui/assets/player7.glb");
        _models["player7"]->setScale(_models["player7"]->scaleToSize(4.0f));

        _models["player8"] = std::make_shared<ModelInfo>("gui/assets/player8.glb");
        _models["player8"]->setScale(_models["player8"]->scaleToSize(7.0f));

        /* background */
        _models["background"] = std::make_shared<ModelInfo>("gui/assets/background.glb");
        _models["background"]->setScale(_models["background"]->scaleToSize(1000.0f));

        /* incantation */
        _models["incantation"] = std::make_shared<ModelInfo>("gui/assets/incantation.glb");
        _models["incantation"]->setScale(_models["incantation"]->scaleToSize(4.5f));
    }

    void AssetsManager::unloadAssets()
    {
        for (auto &[key, model] : _models) {
            DEBUG << "Unloading model: " << key;
            for (auto &texture : model->getTextures()) {
            // CA SEGFAULT JE SAIS PAS PQ
                // UnloadTexture(texture);
            }
            // CA SEGFAULT JE SAIS PAS PQ
            // UnloadModel(model->getModel());
        }
        _models.clear();
    }

    std::unordered_map<std::string, std::shared_ptr<ModelInfo>> &AssetsManager::getModels(void)
    {
        return _models;
    }

    Texture2D AssetsManager::getResourceIcon(PlayerInfo::ResourceType Key)
    {
        static std::unordered_map<PlayerInfo::ResourceType, Texture2D> resourceIcons;

        if (resourceIcons.empty()) {
            resourceIcons[PlayerInfo::ResourceType::FOOD] = LoadTexture("gui/assets/food.png");
            resourceIcons[PlayerInfo::ResourceType::LINEMATE] = LoadTexture("gui/assets/linemate.png");
            resourceIcons[PlayerInfo::ResourceType::DERAUMERE] = LoadTexture("gui/assets/deraumere.png");
            resourceIcons[PlayerInfo::ResourceType::SIBUR] = LoadTexture("gui/assets/sibur.png");
            resourceIcons[PlayerInfo::ResourceType::MENDIANE] = LoadTexture("gui/assets/mendiane.png");
            resourceIcons[PlayerInfo::ResourceType::PHIRAS] = LoadTexture("gui/assets/phiras.png");
            resourceIcons[PlayerInfo::ResourceType::THYSTAME] = LoadTexture("gui/assets/thystame.png");
        }

        return resourceIcons[Key];
    }
}