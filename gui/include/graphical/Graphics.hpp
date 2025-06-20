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
    #include "AssetsManager.hpp"
    #include "GameInfo.hpp"
    #include "MenuInfo.hpp"
#include "PauseInfo.hpp"
    #include "raylib.h"
    #include <cstring>
    #include "QueueManager.hpp"
    #include "Chatbox.hpp"


/**
 * @file Graphics.hpp
 * @brief The Graphics class for managing the graphical interface
 * @author Gianni TUERO
 */

namespace Gui {
    constexpr size_t WINDOW_WIDTH = 1200;     ///< Default window width
    constexpr size_t WINDOW_HEIGHT = 600;     ///< Default window height
    constexpr float TILE_SIZE = 5.0;          ///< Size of each tile in the game world

    /**
     * @class Graphics
     * @brief Manages the graphical interface and rendering of the game
     */
    class Graphics {
        public:
            /**
             * @enum ConnectionState
             * @brief Represents the state of the connection to the server
             */
            enum ConnectionState {
                WELCOME_STATE,    ///< Initial connection state waiting for welcome message
                TEAM_NAME,        ///< State when sending team name to server
            };

            /**
             * @enum Scene
             * @brief Represents the current scene being displayed
             */
            enum Scene {
                MENU,           ///< Main menu scene
                GAME,           ///< Game play scene
                SCOREBOARD,     ///< Scoreboard display scene
                PAUSE,          ///< Pause menu scene
            };
        public:
            /**
             * @brief Constructor for the Graphics class
             * @param queueManager Shared pointer to the QueueManager for communication
             */
            Graphics(std::shared_ptr<QueueManager> queueManager);

            /**
             * @brief Destructor for the Graphics class
             * Closes the window if it's still open
             */
            ~Graphics();

        ////////////////////////////////////// GETTERS //////////////////////////////////////
            /**
             * @brief Gets the reference to the current scene
             * @return Reference to the current Scene enum value
             */
            Scene &getScene(void) { return _scene; }

            /**
             * @brief Gets the reference to the game information
             * @return Shared pointer reference to the GameInfo object
             */
            std::shared_ptr<GameInfo> &getGame(void) { return _game; }

            /**
             * @brief Gets the reference to the menu information
             * @return Shared pointer reference to the MenuInfo object
             */
            std::shared_ptr<MenuInfo> &getMenu(void) { return _menu; }

            /**
             * @brief Gets the reference to the chatbox
             * @return Shared pointer reference to the Chatbox object
             */
            std::shared_ptr<Chatbox> &getChatbox(void) { return _chatbox; }

            /**
             * @brief Gets the reference to the mouse position
             * @return Reference to the Vector2 containing mouse coordinates
             */
            Vector2 &getMousePos(void) { return _mousePos; }

            /**
             * @brief Gets the reference to the queue manager
             * @return Shared pointer reference to the QueueManager object
             */
            std::shared_ptr<QueueManager> &getQueueManager(void) { return _queueManager; }

            /**
             * @brief Current connection state with the server
             */
            ConnectionState state;

            /**
             * @brief Gets the reference to the assets manager
             * @return Reference to the AssetsManager object
             */
            AssetsManager &getAssetsManager(void) { return _assetsManager; }

            /**
             * @brief Sets the pause menu information
             * @param pause Shared pointer to the PauseInfo object
             */
            void setPause(std::shared_ptr<PauseInfo> pause) { _pause = pause; }

            /**
             * @brief Gets the reference to the pause menu information
             * @return Shared pointer reference to the PauseInfo object
             */
            std::shared_ptr<PauseInfo> &getPause(void) { return _pause; }


        ////////////////////////////////////// GRAPHIC //////////////////////////////////////
            /**
             * @brief Initializes the graphics system
             * Sets up the window, frame rate, and callback mappings
             */
            void init(void);

            /**
             * @brief Main run loop for the graphics system
             * @param isRunning Atomic boolean reference to control program execution
             */
            void run(std::atomic<bool> &);

        private:
            /**
             * @brief Handles all input events based on the current scene
             */
            void handleEvents(void);

            /**
             * @brief Updates the game state based on the current scene
             */
            void update(void);

            /**
             * @brief Renders the current scene
             */
            void draw(void);

            /**
             * @brief Switches to pause scene from another scene
             * @param previousScene The scene to return to when exiting pause
             */
            void switchToPause(Scene previousScene);

        ////////////////////////////////////// MENU //////////////////////////////////////
        private:
            /**
             * @brief Handles input events for the menu scene
             */
            void handleEventsMenu(void);

            /**
             * @brief Updates the menu scene state
             */
            void updateMenu(void);

            /**
             * @brief Renders the menu scene
             */
            void drawMenu(void);

        ////////////////////////////////////// GAME //////////////////////////////////////
        private:
            /**
             * @brief Handles input events for the game scene
             */
            void handleEventsGame(void);

            /**
             * @brief Updates the game scene state
             */
            void updateGame(void);

            /**
             * @brief Renders the game scene
             */
            void drawGame(void);

            /**
             * @brief Renders the game map with all tiles
             */
            void drawGameMap(void);

            /**
             * @brief Renders the team information display
             */
            void drawTeams(void);

            /**
             * @brief Renders all players on the map
             */
            void drawPlayers(void);

            /**
             * @brief Renders a specific player on a tile
             * @param id The player's ID
             * @param player Shared pointer to the PlayerInfo object
             * @param tile The tile the player is on
             */
            void drawPlayer(int id, std::shared_ptr<PlayerInfo> &player, TileInfo &tile);

            /**
             * @brief Renders the selected player's inventory
             */
            void drawPlayerInventory();

            /**
             * @brief Renders name tags above players
             */
            void drawPlayerTag();

        ////////////////////////////////////// SCOREBOARD //////////////////////////////////////
        private:
            /**
             * @brief Handles input events for the scoreboard scene
             */
            void handleEventsScoreboard();

            /**
             * @brief Updates the scoreboard scene state
             */
            void updateScoreboard();

            /**
             * @brief Renders the scoreboard scene
             */
            void drawScoreboard();

            /**
             * @brief Renders the column headers in the scoreboard
             */
            void drawTabs();

        ////////////////////////////////////// PAUSE //////////////////////////////////////
        private:
            /**
             * @brief Handles input events for the pause scene
             */
            void handleEventsPause(void);

            /**
             * @brief Updates the pause scene state
             */
            void updatePause(void);

            /**
             * @brief Renders the pause scene
             */
            void drawPause(void);

            /**
             * @brief Returns to the scene that was active before entering pause
             */
            void switchToPreviousScene(void);

        private:
            std::shared_ptr<QueueManager> _queueManager;  ///< Queue manager for communication with server
            Scene _scene;                                 ///< Current active scene
            Scene _previousScene;                         ///< Scene to return to after pause
            Vector2 _mousePos;                            ///< Current mouse position
            std::unordered_map<Scene, void (Graphics::*)(void)> _handlers;  ///< Map of scene event handlers
            std::unordered_map<Scene, void (Graphics::*)(void)> _updaters;  ///< Map of scene update functions
            std::unordered_map<Scene, void (Graphics::*)(void)> _drawers;   ///< Map of scene drawing functions


            std::shared_ptr<MenuInfo> _menu;        ///< Menu scene information
            std::shared_ptr<GameInfo> _game;        ///< Game scene information
            std::shared_ptr<PauseInfo> _pause;      ///< Pause scene information
            std::shared_ptr<Chatbox> _chatbox;      ///< Chat display and messaging

            AssetsManager _assetsManager;           ///< Manager for game assets and resources

            bool _windowShouldRun;                  ///< Flag controlling window operation
    };
}

#endif // GRAPHICS_HPP