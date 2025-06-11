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
#include <tuple>

namespace Gui {
    AssetsManager::~AssetsManager()
    {
        unloadAssets();
    }
    void AssetsManager::loadAssets()
    {
        /* food */
        /* std::shared_ptr<ModelInfo> cupcakeInfo = std::make_shared<ModelInfo>("gui/assets/cupcake/cupcake.gltf", 0.3f);
        std::vector<Texture2D> cupcakeTextures = {
            LoadTexture("gui/assets/cupcake/textures/cupcake0.jpeg"),
            LoadTexture("gui/assets/cupcake/textures/cupcake1.jpeg")
        };
        cupcakeInfo->setTextures(cupcakeTextures);
        cupcakeInfo->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cupcakeTextures[1];
        cupcakeInfo->getModel().materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = cupcakeTextures[0];
        cupcakeInfo->getModel().materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = cupcakeTextures[1];
        cupcakeInfo->getModel().materials[3].maps[MATERIAL_MAP_DIFFUSE].texture = cupcakeTextures[0]; */
        _models["food"] = std::make_shared<ModelInfo>("gui/assets/box.glb");
        _models["food"]->setScale(_models["food"]->scaleToSize(1.0f));



        /* linemate */
        // std::shared_ptr<ModelInfo> magic_stone = std::make_shared<ModelInfo>("gui/assets/magic_stone/scene.gltf", 15.0f);
        // std::vector<Texture2D> magicStoneTextures = {
        //     LoadTexture("gui/assets/magic_stone/textures/lambert2_baseColor.png"),
        //     LoadTexture("gui/assets/magic_stone/textures/lambert2_metallicRoughness.png"),
        //     LoadTexture("gui/assets/magic_stone/textures/lambert2_emissive.png"),
        //     LoadTexture("gui/assets/magic_stone/textures/lambert2_normal.png")
        // };
        // magic_stone->setTextures(magicStoneTextures);
        // magic_stone->getModel().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = magicStoneTextures[0];
        // magic_stone->getModel().materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = magicStoneTextures[1];
        // magic_stone->getModel().materials[0].maps[MATERIAL_MAP_EMISSION].texture = magicStoneTextures[2];
        // magic_stone->getModel().materials[0].maps[MATERIAL_MAP_NORMAL].texture = magicStoneTextures[3];
        _models["linemate"] = std::make_shared<ModelInfo>("gui/assets/iron.glb");
        _models["linemate"]->setScale(_models["linemate"]->scaleToSize(1.0f));

        _models["deraumere"] = std::make_shared<ModelInfo>("gui/assets/gold.glb");
        _models["deraumere"]->setScale(_models["deraumere"]->scaleToSize(1.0f));


        /* sibur */
        _models["sibur"] = std::make_shared<ModelInfo>("gui/assets/redstone.glb");
        _models["sibur"]->setScale(_models["sibur"]->scaleToSize(1.0f));

        /* mendiane */
        _models["mendiane"] = std::make_shared<ModelInfo>("gui/assets/flower.glb");
        _models["mendiane"]->setScale(_models["mendiane"]->scaleToSize(1.0f));

        /* phiras */
        _models["phiras"] = std::make_shared<ModelInfo>("gui/assets/diamond.glb");
        _models["phiras"]->setScale(_models["phiras"]->scaleToSize(1.0f));

        /* thystame */
        _models["thystame"] = std::make_shared<ModelInfo>("gui/assets/emerald.glb");
        _models["thystame"]->setScale(_models["thystame"]->scaleToSize(1.0f));

        /* island */
        _models["island"] = std::make_shared<ModelInfo>("gui/assets/grass.glb", 1.0f);
        _models["island"]->setScale(_models["island"]->scaleToSize(TILE_SIZE - 0.5));

        // /* player */
        _models["player"] = std::make_shared<ModelInfo>("gui/assets/steve.glb");
        _models["player"]->setScale(_models["player"]->scaleToSize(2.0f));

        // /* background */
        _models["background"] = std::make_shared<ModelInfo>("gui/assets/bg2.glb", 1.0f);
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
}