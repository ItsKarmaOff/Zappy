/*
** EPITECH PROJECT, 2025
** AssetsManager.hpp
** File description:
** AssetsManager declaration
*/


#ifndef ASSETSMANAGER_HPP
    #define ASSETSMANAGER_HPP

#include <raylib.h>
#include <string>
#include <unordered_map>
namespace Gui {

    class AssetsManager {
        public:
            AssetsManager() = default;
            ~AssetsManager() = default;

            // Load assets
            void loadAssets();
            // Unload assets
            void unloadAssets();

            // Getters for assets
            std::unordered_map<std::string, Model> &getModels(void);
            std::unordered_map<std::string, Texture2D> &getTextures(void);

        private:

            std::unordered_map<std::string, Model> _models;
            std::unordered_map<std::string, Texture2D> _textures;

    };

}

#endif // ASSETSMANAGER_HPP