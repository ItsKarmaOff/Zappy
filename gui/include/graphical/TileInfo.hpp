/*
** EPITECH PROJECT, 2025
** TileInfo.hpp
** File description:
** TileInfo declaration
*/


#ifndef TILEINFO_HPP
    #define TILEINFO_HPP

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

            std::unordered_map<std::string, int> &getContent(void);
            void setPos(const std::unordered_map<std::string, int> &cont);

            ////////////////////////////////////// UTILITY //////////////////////////////////////
            void draw(std::unordered_map<std::string, Model> &models);

        private:
            Vector3 _pos;
            std::unordered_map<std::string, int> _content;

    };


}

#endif // TILEINFO_HPP