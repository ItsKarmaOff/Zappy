/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The TileInfo class declaration
*/
/**
 * @file TileInfo.hpp
 * @brief The TileInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef TILEINFO_HPP
    #define TILEINFO_HPP

    #include "AssetsManager.hpp"

/**
 * @file TileInfo.hpp
 * @brief The TileInfo class for representing tile data in the game
 * @author Gianni TUERO
 */

namespace Gui
{
    class TileInfo {
        public:

            //////////////// Constructors and Destructor ///////////////////////

            TileInfo(const Vector3 &pos);
            TileInfo();
            ~TileInfo() = default;



            //////////////// Getters ///////////////////////////////////////////

            const Vector3 &getPos() const;
            void setPos(const Vector3 &pos);
            std::map<std::string, int> &getContent(void);



            //////////////// Setters ///////////////////////////////////////////

            void setContent(const std::map<std::string, int> &cont);



            //////////////// Main Methods //////////////////////////////////////

            /**
             * @brief Draw the tile
             * @param assetsManager Reference to the AssetsManager
             */
            void draw(AssetsManager &assetsManager);
            /**
             * @brief Draw the tile content
             * @param assetsManager Reference to the AssetsManager
             */
            void drawContent(AssetsManager &assetsManager) const;



        private:
            Vector3 _pos; ///< Position of the tile in 3D space
            std::map<std::string, int> _content; ///< Map of content on the tile, e.g., resources and their quantities
    };
}

#endif // TILEINFO_HPP