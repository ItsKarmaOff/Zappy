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
#include <queue>
#include <string>
    #include <unordered_map>
#include "AssetsManager.hpp"
    #include "GameInfo.hpp"
#include "MenuInfo.hpp"
    #include "raylib.h"
    #include <cstring>
#include <vector>
#include "QueueManager.hpp"



namespace Gui {
    constexpr size_t WINDOW_WIDTH = 1200;
    constexpr size_t WINDOW_HEIGHT = 600;
    constexpr float TILE_SIZE = 5.0;

    class Graphics {
        public:
            enum ConnectionState {
                WELCOME_STATE,
                TEAM_NAME,
            };

            enum Scene {
                MENU,
                GAME,
                SCOREBOARD,
            };
        public:
            Graphics(std::shared_ptr<QueueManager> queueManager);
            ~Graphics();

        ////////////////////////////////////// GETTERS //////////////////////////////////////
            Scene &getScene(void) { return _scene; }
            std::shared_ptr<GameInfo> &getGame(void) { return _game; }
            std::shared_ptr<MenuInfo> &getMenu(void) { return _menu; }
            Vector2 &getMousePos(void) { return _mousePos; }
            std::shared_ptr<QueueManager> &getQueueManager(void) { return _queueManager; }
            ConnectionState state;
            AssetsManager &getAssetsManager(void) { return _assetsManager; }


        ////////////////////////////////////// GRAPHIC //////////////////////////////////////
            void init(void);
            void run(std::atomic<bool> &);

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
            void drawGameMap(void);
            void drawTeams(void);
            void drawPlayers(void);

        ////////////////////////////////////// SCOREBOARD //////////////////////////////////////
        private:
            void handleEventsScoreboard();
            void updateScoreboard();
            void drawScoreboard();
            void drawTabs();

        private:
            std::shared_ptr<QueueManager> _queueManager;
            Scene _scene;
            Vector2 _mousePos;
            std::unordered_map<Scene, void (Graphics::*)(void)> _handlers;
            std::unordered_map<Scene, void (Graphics::*)(void)> _updaters;
            std::unordered_map<Scene, void (Graphics::*)(void)> _drawers;


            std::shared_ptr<MenuInfo> _menu;
            std::shared_ptr<GameInfo> _game;
            AssetsManager _assetsManager;
            // int = temporaire
    };
}

#endif // GRAPHICS_HPP