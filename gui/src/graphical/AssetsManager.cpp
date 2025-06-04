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
        /* cupcake */
        Model cupcake = LoadModel("gui/assets/cupcake/cupcake.gltf");
        Texture2D tex0 = LoadTexture("gui/assets/cupcake/textures/cupcake0.jpeg");
        Texture2D tex1 = LoadTexture("gui/assets/cupcake/textures/cupcake1.jpeg");
        // Texture2D tex2 = LoadTexture("gui/assets/cupcake/textures/cupcake2.jpeg");
        cupcake.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex1;
        cupcake.materials[1].maps[MATERIAL_MAP_DIFFUSE].texture = tex0;
        cupcake.materials[2].maps[MATERIAL_MAP_DIFFUSE].texture = tex1;
        cupcake.materials[3].maps[MATERIAL_MAP_DIFFUSE].texture = tex0;

        Model magic_stone = LoadModel("gui/assets/magic_stone/scene.gltf");
        Texture2D baseColor = LoadTexture("gui/assets/magic_stone/textures/lambert2_baseColor.png");
        Texture2D roughness = LoadTexture("gui/assets/magic_stone/textures/lambert2_metallicRoughness.png");
        Texture2D emissive  = LoadTexture("gui/assets/magic_stone/textures/lambert2_emissive.png");
        Texture2D normal    = LoadTexture("gui/assets/magic_stone/textures/lambert2_normal.png");
        magic_stone.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = baseColor;
        magic_stone.materials[0].maps[MATERIAL_MAP_ROUGHNESS].texture = roughness;
        magic_stone.materials[0].maps[MATERIAL_MAP_EMISSION].texture = emissive;
        magic_stone.materials[0].maps[MATERIAL_MAP_NORMAL].texture = normal;

        _models["food"] = cupcake;
        _models["linemate"] = magic_stone;
        _models["island"] = LoadModel("gui/assets/island/island.gltf");
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

    std::unordered_map<std::string, Texture2D> &AssetsManager::getTextures(void)
    {
        return _textures;
    }

}