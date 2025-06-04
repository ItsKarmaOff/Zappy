/*
** EPITECH PROJECT, 2025
** GameInfo.hpp
** File description:
** GameInfo declaration
*/


#ifndef GAMEINFO_HPP
    #define GAMEINFO_HPP

    #include <raylib.h>

namespace Gui {

    class GameInfo {
        public:
            GameInfo();
            ~GameInfo() = default;

            Camera3D &getCamera();
            Vector2 &getMapSize();
        private:
            Camera3D _camera;
            Vector2 _mapSize;
    };

}

#endif // GAMEINFO_HPP