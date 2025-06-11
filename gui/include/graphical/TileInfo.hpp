/*
** EPITECH PROJECT, 2025
** TileInfo.hpp
** File description:
** TileInfo declaration
*/


#ifndef TILEINFO_HPP
    #define TILEINFO_HPP

#include "AssetsManager.hpp"
#include <map>
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace Gui {
    class TileInfo {
        public:
            TileInfo(const Vector3 &pos);
            TileInfo();
            ~TileInfo() = default;

            ////////////////////////////////////// GETTERS //////////////////////////////////////
            const Vector3 &getPos() const;
            void setPos(const Vector3 &pos);

            std::map<std::string, int> &getContent(void);
            void setContent(const std::map<std::string, int> &cont);

            ////////////////////////////////////// UTILITY //////////////////////////////////////
            void draw(AssetsManager &assetsManager);

        private:
            Vector3 _pos;
            std::map<std::string, int> _content;

    };


}

#endif // TILEINFO_HPP