/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The AssetsManager class declaration
*/
/**
 * @file AssetsManager.hpp
 * @brief The AssetsManager class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef ASSETSMANAGER_HPP
    #define ASSETSMANAGER_HPP

    #include "ModelInfo.hpp"
    #include "PlayerInfo.hpp"

namespace Gui
{
    /**
     * @brief Class managing game assets
     * @details This class is responsible for loading, unloading, and providing access to game assets
     * such as 3D models.
     */
    class AssetsManager {
        public:

            //////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Default constructor
             */
            AssetsManager() = default;

            /**
             * @brief Destructor
             */
            ~AssetsManager();



            //////////////// Main Methods //////////////////////////////////////

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
             * @param Key The resource type key
             * @return The texture associated with the resource type
             */
            Texture2D getResourceIcon(PlayerInfo::ResourceType Key);

            /**
             * @brief Gets the map containing all loaded textures
             * @return Reference to the unordered map of textures
             */
            static std::unordered_map<std::string, std::shared_ptr<Texture2D>> &getTextures(void);



        private:

            //////////////// Private Attributes ////////////////////////////////

            std::unordered_map<std::string, std::shared_ptr<ModelInfo>> _models; //< Map of loaded models
    };
}

#endif // ASSETSMANAGER_HPP
