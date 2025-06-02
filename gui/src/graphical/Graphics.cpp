/*
** EPITECH PROJECT, 2025
** Graphics.cpp
** File description:
** Graphics in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/Graphics
*/

#include "Graphics.hpp"
#include <raylib.h>

namespace Gui {
    Graphics::Graphics()
    {
        _scene = MENU;
        _game = nullptr;
    }

    Graphics::~Graphics()
    {
        if (IsWindowReady())
            CloseWindow();
    }

    void Graphics::init(void)
    {
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Zappy");
        SetTargetFPS(60);

        _handlers = {
            {MENU, &Graphics::handleEventsMenu},
            {GAME, &Graphics::handleEventsGame},
        };

        _updaters = {
            {MENU, &Graphics::updateMenu},
            {GAME, &Graphics::updateGame},
        };

        _drawers = {
            {MENU, &Graphics::drawMenu},
            {GAME, &Graphics::drawGame},
        };
    }


    void Graphics::run(void)
    {
        while (!WindowShouldClose()) {
            _mousePos = GetMousePosition();
            handleEvents();
            update();
            draw();
        }
    }

    void Graphics::handleEvents(void)
    {
        (this->*_handlers[_scene])();
    }

    void Graphics::update(void)
    {
        (this->*_updaters[_scene])();
    }

    void Graphics::draw(void)
    {
        BeginDrawing();
        (this->*_drawers[_scene])();
        EndDrawing();
    }
}