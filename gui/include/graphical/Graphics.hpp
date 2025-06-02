/*
** EPITECH PROJECT, 2025
** Graphics.hpp
** File description:
** Graphics declaration
*/


#ifndef GRAPHICS_HPP
    #define GRAPHICS_HPP
    #include <cstddef>
    #include <memory>
    #include <unordered_map>
    #include "GameInfo.hpp"
    #include "raylib.h"
    #include <cstring>



namespace Gui {
    constexpr size_t WINDOW_WIDTH = 1200;
    constexpr size_t WINDOW_HEIGHT = 600;

    class Graphics {
        public:
            enum Scene {
                MENU,
                GAME,
            };
        public:
            Graphics();
            ~Graphics();

            void init(void);
            void run(void);
        private:
            void handleEvents(void);
            void update(void);
            void draw(void);

        ////////////////////////////////////// MENU //////////////////////////////////////
        private:
            void handleEventsMenu(void);
            void updateMenu(void);
            void drawMenu(void);

        ////////////////////////////////////// GAME //////////////////////////////////////
        private:
            void handleEventsGame(void);
            void updateGame(void);
            void drawGame(void);

        private:
            Scene _scene;
            std::unordered_map<Scene, void (Graphics::*)(void)> _handlers;
            std::unordered_map<Scene, void (Graphics::*)(void)> _updaters;
            std::unordered_map<Scene, void (Graphics::*)(void)> _drawers;

            std::shared_ptr<GameInfo> _game;
            Vector2 _mousePos;
    };
}

#endif // GRAPHICS_HPP