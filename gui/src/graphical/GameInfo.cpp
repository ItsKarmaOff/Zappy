/*
** EPITECH PROJECT, 2025
** GameInfo.cpp
** File description:
** GameInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "GameInfo.hpp"
#include <raylib.h>

namespace Gui {
    GameInfo::GameInfo()
    : _camera()
    {
        _camera.position = {10.0f, 10.0f, 10.0f};
        _camera.target = {0, 0, 0};
        _camera.up = {0, 1.0, 0};
        _camera.projection = CAMERA_PERSPECTIVE;
        _camera.fovy = 45.0f;
    }

    Camera3D& GameInfo::getCamera()
    {
        return _camera;
    }

}