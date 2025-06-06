/*
** EPITECH PROJECT, 2025
** AssetsManager.cpp
** File description:
** AssetsManager in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "AssetsManager.hpp"
#include "Logs.hpp"

namespace Gui {
    void AssetsManager::loadAssets()
    {
        /* food */
        Model cupcake = LoadModel("gui/assets/cupcake/cupcake.gltf");
        Texture2D tex0 = LoadTexture("gui/assets/cupcake/textures/cupcake0.jpeg");
        Texture2D tex1 = LoadTexture("gui/assets/cupcake/textures/cupcake1.jpeg");
        // Texture2D tex2 = LoadTexture("gui/assets/cupcake/textures/cupcake2.jpeg");
        cupcake.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex1;
        cupcake.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = tex0;
        cupcake.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = tex1;
        cupcake.materials[3].maps[MATERIAL_MAP_DIFFUSE].texture = tex0;
        _models["food"] = cupcake;
        _modelsScale["food"] = 0.3f;
        _textures["cup0"] = tex0;
        _textures["cup1"] = tex1;


        /* linemate */
        Model magic_stone = LoadModel("gui/assets/magic_stone/scene.gltf");
        Texture2D baseColor = LoadTexture("gui/assets/magic_stone/textures/lambert2_baseColor.png");
        Texture2D roughness = LoadTexture("gui/assets/magic_stone/textures/lambert2_metallicRoughness.png");
        Texture2D emissive  = LoadTexture("gui/assets/magic_stone/textures/lambert2_emissive.png");
        Texture2D normal    = LoadTexture("gui/assets/magic_stone/textures/lambert2_normal.png");
        magic_stone.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = baseColor;
        magic_stone.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = roughness;
        magic_stone.materials[0].maps[MATERIAL_MAP_EMISSION].texture = emissive;
        magic_stone.materials[0].maps[MATERIAL_MAP_NORMAL].texture = normal;
        _models["linemate"] = magic_stone;
        _modelsScale["linemate"] = 15.0f;
        _textures["magic_stone0"] = baseColor;
        _textures["magic_stone1"] = roughness;
        _textures["magic_stone2"] = emissive;
        _textures["magic_stone3"] = normal;

        /* sibur */
        Model sibur = LoadModel("gui/assets/sibur/scene.gltf");
        Texture2D baseColor1 = LoadTexture("gui/assets/sibur/textures/baseColor.png");
        Texture2D roughness1 = LoadTexture("gui/assets/sibur/textures/metallicRoughness.png");
        Texture2D emissive1  = LoadTexture("gui/assets/sibur/textures/emissive.png");
        Texture2D normal1    = LoadTexture("gui/assets/sibur/textures/normal.png");
        sibur.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = baseColor1;
        sibur.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = roughness1;
        sibur.materials[0].maps[MATERIAL_MAP_EMISSION].texture = emissive1;
        sibur.materials[0].maps[MATERIAL_MAP_NORMAL].texture = normal1;
        _models["sibur"] = sibur;
        _modelsScale["sibur"] = 5.0f;
        _textures["sibur0"] = baseColor1;
        _textures["sibur1"] = roughness1;
        _textures["sibur2"] = emissive1;
        _textures["sibur3"] = normal1;

        /* mendiane */
        _models["mendiane"] = LoadModel("gui/assets/mendiane.glb");
        _modelsScale["mendiane"] = 0.05f;

        /* phiras */
        _models["phiras"] = LoadModel("gui/assets/phiras.glb");
        _modelsScale["phiras"] = 0.3f;

        /* thystame */
        _models["thystame"] = LoadModel("gui/assets/thystame.glb");
        _modelsScale["thystame"] = 0.05f;

        /* island */
        _models["island"] = LoadModel("gui/assets/island/island.gltf");
        _modelsScale["island"] = 0.5f;
    }


    void AssetsManager::unloadAssets()
    {
        // Unload the apple model and texture
        for (auto &[key, model] : _models) {
            UnloadModel(model);
        }
        for (auto &[key, texture] : _textures) {
            UnloadTexture(texture);
        }
    }


    std::unordered_map<std::string, Model> &AssetsManager::getModels(void)
    {
        return _models;
    }
    std::unordered_map<std::string, float> &AssetsManager::getModelsScale(void)
    {
        return _modelsScale;
    }

    std::unordered_map<std::string, Texture2D> &AssetsManager::getTextures(void)
    {
        return _textures;
    }

}