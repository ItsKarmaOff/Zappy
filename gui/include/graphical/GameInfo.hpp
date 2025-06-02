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
        private:
            Camera3D _camera;
    };

}

#endif // GAMEINFO_HPP