/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Game scene implementation
*/
/**
 * @file Game.cpp
 * @brief The Game scene implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Graphics.hpp"

namespace Gui {
    void Graphics::handleEventsGame(void)
    {
        // on peut pas modifier la touche, mais Z = W (dcp faut appuyer sur W)
        if (IsKeyPressed(KEY_Z)) {
            _game->getCamera().target =
            { _game->getMapSize().x / 2 * TILE_SIZE, 0.0f, _game->getMapSize().y / 2 * TILE_SIZE };
        }
        if (IsKeyPressed(KEY_TAB)) {
            _scene = SCOREBOARD;
            EnableCursor();
        }if (IsKeyReleased(KEY_F)) {
            VarManager::getInstance().setVar(VarManager::DEBUG_VAR, !VarManager::getInstance().getVar(VarManager::DEBUG_VAR));
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            if (IsCursorHidden())
                EnableCursor();
            else
                DisableCursor();
        }
        // check if player is selected
        if (!IsCursorHidden() && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            Ray ray = GetScreenToWorldRay(_mousePos, _game->getCamera());
            for (auto &[id, player] : _game->getPlayers())
                player->setSelected(false);
            for (auto &[id, player] : _game->getPlayers()) {
                std::shared_ptr<ModelInfo> model = _assetsManager.getModels()["player" + std::to_string(player->getLevel())];
                TileInfo &tile = _game->getTiles()[{player->getPos().x, player->getPos().y}];
                Vector3 pos = {
                    tile.getPos().x,
                    model->getAligned(model->getBoundingBox().min.y),
                    tile.getPos().z
                };
                float rotation = -90 * player->getOrientation();
                BoundingBox playerBoundingBox = model->getBoundingBoxForCollision(pos, rotation);
                RayCollision collision = GetRayCollisionBox(ray, playerBoundingBox);

                player->setSelected(collision.hit);
                if (collision.hit) {
                    //std::string player = "#" + std::to_string(id);
                    _queueManager->pushCommand({"pin", "#" + std::to_string(id)});
                    break;
                }
            }
        }
        // if N is pressed, select next player
        if (IsKeyPressed(KEY_LEFT)) {
            bool foundSelected = false;
            for (auto &[id, player] : _game->getPlayers()) {
                if (player->isSelected()) {
                    foundSelected = true;
                    break;
                }
            }
            if (!foundSelected) {
                // if no player is selected, select the first one
                for (auto &[id, player] : _game->getPlayers()) {
                    player->setSelected(true);
                    break;
                }
                return;
            }
            for (auto &[id, player] : _game->getPlayers()) {
                if (player->isSelected()) {
                    player->setSelected(false);
                    auto it = _game->getPlayers().find(id);
                    if (it != _game->getPlayers().end()) {
                        ++it;
                        if (it == _game->getPlayers().end())
                            it = _game->getPlayers().begin();
                        it->second->setSelected(true);
                    }
                    break;
                }
            }
        }

        // if P is pressed, select previous player
        if (IsKeyPressed(KEY_RIGHT)) {
            bool foundSelected = false;
            for (auto &[id, player] : _game->getPlayers()) {
                if (player->isSelected()) {
                    foundSelected = true;
                    break;
                }
            }
            if (!foundSelected) {
                // if no player is selected, select the first one
                for (auto &[id, player] : _game->getPlayers()) {
                    player->setSelected(true);
                    break;
                }
                return;
            }
            // Since unordered_map doesn't have reverse iterators, we'll use a vector of player IDs
            std::vector<int> playerIds;
            for (auto &[id, player] : _game->getPlayers())
                playerIds.push_back(id);

            // Find the selected player and select the previous one
            for (int i = playerIds.size() - 1; i >= 0; i--) {
                int id = playerIds[i];
                if (_game->getPlayers()[id]->isSelected()) {
                    _game->getPlayers()[id]->setSelected(false);
                    int prevIndex = (i - 1 >= 0) ? i - 1 : playerIds.size() - 1;
                    _game->getPlayers()[playerIds[prevIndex]]->setSelected(true);
                    break;
                }
            }
        }


        if (IsKeyReleased(KEY_ESCAPE)) {
            bool playerSelected = false;
            for (auto &[id, player] : _game->getPlayers()) {
                if (player->isSelected()) {
                    player->setSelected(false);
                    playerSelected = true;
                    break;
                }
            }
            if (!playerSelected) {
                switchToPause(GAME);
            }
        }
    }

    void Graphics::updateGame(void)
    {
        if (!IsMusicStreamPlaying(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]))
            PlayMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]);
        UpdateMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]);
        for (auto &[id, player] : _game->getPlayers()) {
            if (player->isSelected()) {
                _game->getCamera().target = {
                    player->getPos().x * TILE_SIZE,
                    0.0f,
                    player->getPos().y * TILE_SIZE
                };
                _game->getCamera().position = {
                    player->getPos().x * TILE_SIZE - 10.0f,
                    10.0f,
                    player->getPos().y * TILE_SIZE - 10.0f
                };
                return;
            }
        }
        if (IsCursorHidden()) {
            UpdateCamera(&_game->getCamera(), CAMERA_FREE);
        }
    }

    void Graphics::drawGame(void)
    {
        ClearBackground(RAYWHITE);

        BeginMode3D(_game->getCamera());
        drawGameMap();
        drawPlayers();
        Vector3 pos = {_game->getMapSize().x * TILE_SIZE / 2.0f, 0.0f, _game->getMapSize().y * TILE_SIZE / 2.0f};
        DrawModel(_assetsManager.getModels()["background"]->getModel(), pos, _assetsManager.getModels()["background"]->getScale(), WHITE);
        EndMode3D();
        drawTeams();
        drawPlayerInventory();
        drawPlayerTag();
        _chatbox->draw(
            {0, GetScreenHeight() * 2 / 3.f},
            {GetScreenWidth() / 3.f, GetScreenHeight() / 3.f}
        );

    }

    void Graphics::drawGameMap(void)
    {
        for (auto &[k, tile] : _game->getTiles()) {
            tile.draw(_assetsManager);
        }
    }
    void Graphics::drawTeams(void)
    {
        int i = 0;
        for (auto &[key, team] : _game->getTeams()) {
            if (key == "UnknownTeam")
                continue;
            // draw team name
            float textHeight = 40;
            float textWidth = MeasureText(key.c_str(), textHeight);
            DrawText(key.c_str(), GetScreenWidth() - textWidth - 10, 0 + i * textHeight, textHeight, team.getColor());
            i++;
        }
    }
    void Graphics::drawPlayers(void)
    {
        for (auto &[id, player] : _game->getPlayers()) {
            /* if (!_game->getTiles().contains({player->getPos().x, player->getPos().y})) {
                ERROR << "No tile matching the player position.";
                continue;
            } */
            TileInfo &tile =_game->getTiles()[{player->getPos().x, player->getPos().y}];
            drawPlayer(id, player, tile);
        }
    }

    void Graphics::drawPlayer(int id, std::shared_ptr<PlayerInfo> &player, TileInfo &tile)
    {
        std::string modelKey = "player" + std::to_string(player->getLevel());
        std::shared_ptr<ModelInfo> playerModel = _assetsManager.getModels()[modelKey];
        std::shared_ptr<ModelInfo> incantationModel = _assetsManager.getModels()["incantation"];
        playerModel->getModel().transform = MatrixRotateY(DEG2RAD * (-90 * player->getOrientation()));
        playerModel->draw(
            {tile.getPos().x, playerModel->getAligned(playerModel->getBoundingBox().min.y), tile.getPos().z},
            player->getColor()
        );
        if (player->isSelected())
            playerModel->drawBoundingBox(GREEN);
        if (player->isIncanting()) {
            incantationModel->draw(
                {tile.getPos().x, incantationModel->getAligned(incantationModel->getBoundingBox().min.y), tile.getPos().z},
                WHITE
            );
        }
    }
    // void Graphics::drawPlayerInventory()
    // {
    //     int i = 0;
    //     int fontSize = GetScreenHeight() / 20;
    //     for (auto &[id, player] : _game->getPlayers()) {
    //         if (player->isSelected()) {
    //             for (auto &[key, nb] : player->getInventory()) {
    //                 std::shared_ptr<ModelInfo> model = _assetsManager.getModels()[ResourceToString.at(key)];
    //                 std::string textToDraw = std::to_string(nb) + " " + ResourceToString.at(key);
    //                 int width = MeasureText(textToDraw.c_str(), fontSize);
    //                 Vector2 pos = {
    //                 GetScreenWidth() - width - 10.0f,
    //                 GetScreenHeight() - (i + 1) * fontSize - 10.0f
    //                 };
    //                 DrawText(textToDraw.c_str(), pos.x, pos.y, fontSize, WHITE);
    //                 i++;
    //             }
    //             break;
    //         }
    //     }
    // }

    void Graphics::drawPlayerInventory()
    {
        int i = 0;
        int fontSize = GetScreenHeight() / 20;
        int iconSize = fontSize;
        std::map<PlayerInfo::Orientation, std::string> orientationStrings = {
            {PlayerInfo::Orientation::NORTH, "North"},
            {PlayerInfo::Orientation::EAST, "East"},
            {PlayerInfo::Orientation::SOUTH, "South"},
            {PlayerInfo::Orientation::WEST, "West"}
        };

        for (auto &[id, player] : _game->getPlayers()) {
            if (player->isSelected()) {
                for (auto &[key, nb] : player->getInventory()) {
                    std::shared_ptr<ModelInfo> model = _assetsManager.getModels()[ResourceToString.at(key)];
                    Texture2D resourceIcon = _assetsManager.getResourceIcon(key);
                    std::string numberText = std::to_string(nb);
                    int nomberWidth = MeasureText(numberText.c_str(), fontSize);

                    Vector2 pos = {
                        GetScreenWidth() - iconSize - nomberWidth - 20.0f,
                        GetScreenHeight() - (i + 1) * fontSize - 10.0f
                    };

                    DrawText(numberText.c_str(), pos.x, pos.y, fontSize, WHITE);

                    Vector2 iconPos = {
                        pos.x + nomberWidth + 5.0f,
                        pos.y
                    };

                    Rectangle sourceRec = {0, 0, (float)resourceIcon.width, (float)resourceIcon.height};
                    Rectangle destRec = {iconPos.x, iconPos.y, (float)iconSize, (float)iconSize};
                    Vector2 origin = {0, 0};

                    DrawTexturePro(resourceIcon, sourceRec, destRec, origin, 0.0f, WHITE);
                    i++;
                }
                DrawText(("Pos: " + std::to_string((int)player->getPos().x) + ", " + std::to_string((int)player->getPos().y)).c_str(),
                GetScreenWidth() - MeasureText(("Pos: " + std::to_string((int)player->getPos().x) + ", " + std::to_string((int)player->getPos().y)).c_str(), fontSize) - 5,
                GetScreenHeight() - (i + 1) * fontSize - 10.0f,
                fontSize, player->getColor());
                i++;

                DrawText((orientationStrings[player->getOrientation()]).c_str(),
                GetScreenWidth() - MeasureText((orientationStrings[player->getOrientation()]).c_str(), fontSize) - 5,
                GetScreenHeight() - (i + 1) * fontSize - 10.0f,
                fontSize, player->getColor());
                i++;

                DrawText(("Player#" + std::to_string(id)).c_str(),
                GetScreenWidth() - MeasureText(("Player#" + std::to_string(id)).c_str(), fontSize) - 5,
                GetScreenHeight() - (i + 1) * fontSize - 10.0f,
                fontSize, player->getColor());
                break;
            }
        }
    }

    void Graphics::drawPlayerTag()
    {
        for (auto &[id, player] : _game->getPlayers()) {
            std::string modelKey = "player" + std::to_string(player->getLevel());
            std::shared_ptr<ModelInfo> playerModel = _assetsManager.getModels()[modelKey];
            TileInfo &tile = _game->getTiles()[{player->getPos().x, player->getPos().y}];
            Vector3 textPos = {
                tile.getPos().x,
                playerModel->getAligned(playerModel->getBoundingBox().min.y) + playerModel->getDimensions().y,
                tile.getPos().z
            };
            if (player->getLevel() == 0)
                continue;
            Vector2 textPosScreen = GetWorldToScreenEx(textPos, _game->getCamera(), GetScreenWidth(), GetScreenHeight());
            DrawText(("Player#" + std::to_string(id)).c_str(),
                textPosScreen.x - MeasureText(("Player#" + std::to_string(id)).c_str(), 40) / 2,
                textPosScreen.y,
                40,
                player->getColor());
        }
    }
}
