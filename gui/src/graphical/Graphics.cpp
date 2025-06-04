/*
** EPITECH PROJECT, 2025
** Graphics.cpp
** File description:
** Graphics in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/Graphics
*/

#include "Graphics.hpp"
#include "Commands.hpp"
#include <raylib.h>
#include <atomic>

namespace Gui {
    Graphics::Graphics(std::shared_ptr<QueueManager> queueManager)
        : _queueManager(queueManager), _mousePos({0, 0}), _assetsManager()
    {
        _scene = MENU;
        state = WELCOME_STATE;
        _game = nullptr;
        _menu = nullptr;
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


    void Graphics::run(std::atomic<bool> &isRunning)
    {
        Commands cmd(*this);
        while (!WindowShouldClose() && isRunning == true) {
            _mousePos = GetMousePosition();
            cmd.handleResponses(_queueManager);
            handleEvents();
            update();
            draw();
        }
        isRunning = false;
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