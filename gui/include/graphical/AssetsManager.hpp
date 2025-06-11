/*
** EPITECH PROJECT, 2025
** AssetsManager.hpp
** File description:
** AssetsManager declaration
*/


#ifndef ASSETSMANAGER_HPP
    #define ASSETSMANAGER_HPP

#include "ModelInfo.hpp"
#include <memory>
#include <raylib.h>
#include <string>
#include <tuple>
#include <unordered_map>
namespace Gui {

    class AssetsManager {
        public:
            AssetsManager() = default;
            ~AssetsManager();

            // Load assets
            void loadAssets();
            void unloadAssets();


            // Getters for assets
            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> &getModels(void);

        private:
            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _models;

    };

}

#endif // ASSETSMANAGER_HPP