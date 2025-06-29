/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Graphics class implementation
*/
/**
 * @file Graphics.cpp
 * @brief The Graphics class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Graphics.hpp"
#include "Commands.hpp"

namespace Gui {
    Graphics::Graphics(std::shared_ptr<QueueManager> queueManager)
        : _queueManager(queueManager), _mousePos({0, 0}), _assetsManager()
    {
        _scene = MENU;
        state = WELCOME_STATE;
        _game = nullptr;
        _menu = nullptr;
        _windowShouldRun = true;
    }

    Graphics::~Graphics()
    {
        if (IsWindowReady())
            CloseWindow();
        if (IsAudioDeviceReady())
            CloseAudioDevice();
    }

    void Graphics::init(void)
    {
        InitAudioDevice();
        InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Zappy");
        SetTargetFPS(60);
        SetExitKey(KEY_NULL);

        _handlers = {
            {MENU, &Graphics::handleEventsMenu},
            {GAME, &Graphics::handleEventsGame},
            {SCOREBOARD, &Graphics::handleEventsScoreboard},
            {PAUSE, &Graphics::handleEventsPause},
            {END, &Graphics::handleEventsEnd},
        };

        _updaters = {
            {MENU, &Graphics::updateMenu},
            {GAME, &Graphics::updateGame},
            {SCOREBOARD, &Graphics::updateScoreboard},
            {PAUSE, &Graphics::updatePause},
            {END, &Graphics::updateEnd},
        };

        _drawers = {
            {MENU, &Graphics::drawMenu},
            {GAME, &Graphics::drawGame},
            {SCOREBOARD, &Graphics::drawScoreboard},
            {PAUSE, &Graphics::drawPause},
            {END, &Graphics::drawEnd},
        };
    }


    void Graphics::run(std::atomic<bool> &isRunning)
    {
        Commands cmd(*this);
        while (_windowShouldRun && isRunning) {
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
        if (!_windowShouldRun || !IsWindowReady())
            return;
        (this->*_handlers[_scene])();
    }

    void Graphics::update(void)
    {
        if (!_windowShouldRun || !IsWindowReady())
            return;
        (this->*_updaters[_scene])();
    }

    void Graphics::draw(void)
    {
        if (!_windowShouldRun || !IsWindowReady())
            return;
        BeginDrawing();
        (this->*_drawers[_scene])();
        EndDrawing();
    }
}