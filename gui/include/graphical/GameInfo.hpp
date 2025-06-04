/*
** EPITECH PROJECT, 2025
** GameInfo.hpp
** File description:
** GameInfo declaration
*/


#ifndef GAMEINFO_HPP
    #define GAMEINFO_HPP

    #include "TileInfo.hpp"
    #include <raylib.h>
#include <unordered_map>
    #include <vector>
    #include <functional>


inline bool operator==(const Vector2& lhs, const Vector2& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// Hash function specialization for Vector2
namespace std {
    template<>
    struct hash<Vector2> {
        std::size_t operator()(const Vector2& v) const {
            return std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1);
        }
    };

}

namespace Gui {

    class GameInfo {
        public:
            GameInfo();
            ~GameInfo() = default;

            Camera3D &getCamera();
            Vector2 &getMapSize();

            // std::vector<TileInfo> &getTiles();
            std::unordered_map<Vector2, TileInfo> &getTiles();
        private:
            Camera3D _camera;
            Vector2 _mapSize;

            std::unordered_map<Vector2, TileInfo> _tiles;
            // std::vector<TileInfo> _tiles;
    };

}

#endif // GAMEINFO_HPP