/*
** EPITECH PROJECT, 2025
** AssetsManager.hpp
** File description:
** AssetsManager declaration
*/


#ifndef ASSETSMANAGER_HPP
    #define ASSETSMANAGER_HPP

#include "ModelInfo.hpp"
#include "PlayerInfo.hpp"
#include <memory>
#include <raylib.h>
#include <string>
#include <tuple>
#include <unordered_map>

/**
 * @file AssetsManager.hpp
 * @brief The AssetsManager class
 * @author Gianni TUERO
 */

namespace Gui {

    /**
     * @brief Class managing game assets
     * @details This class is responsible for loading, unloading, and providing access to game assets
     * such as 3D models.
     */
    class AssetsManager {
        public:
            /**
             * @brief Default constructor
             */
            AssetsManager() = default;

            /**
             * @brief Destructor
             */
            ~AssetsManager();

            /**
             * @brief Loads all required assets into memory
             * @details Initializes and loads all required game assets such as 3D models
             */
            void loadAssets();

            /**
             * @brief Unloads all assets from memory
             * @details Properly cleans up and releases all loaded game assets
             */
            void unloadAssets();

            /**
             * @brief Gets the map containing all loaded 3D models
             * @return Reference to the unordered map of models
             */
            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> &getModels(void);

            /**
             * @brief Gets the icon texture for a specific resource type
             * @param Key The resource type for which to get the icon
             * @return The texture representing the resource icon
             */
            Texture2D getResourceIcon(PlayerInfo::ResourceType Key);

        private:
            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _models; //< Map of loaded models

    };

}

#endif // ASSETSMANAGER_HPP