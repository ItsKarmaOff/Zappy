/*
** EPITECH PROJECT, 2025
** SoundsManager.cpp
** File description:
** SoundsManager in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "SoundsManager.hpp"
#include <raylib.h>

namespace Gui {
    SoundsManager::SoundsManager()
    {
        /* sounds */
        _sounds[PICKUP_SOUND] = LoadSound("gui/assets/sounds/pickup.ogg");

        /* music */
        _musics[MENU_SONG] = LoadMusicStream("gui/assets/sounds/sweden.ogg");
        _musics[GAME_SONG] = LoadMusicStream("gui/assets/sounds/sweden_edm.ogg");

        for (auto &sound : _sounds) {
            SetSoundVolume(sound.second, 1.0);
        }
        for (auto &music : _musics) {
            SetMusicVolume(music.second, 1.0);
            PlayMusicStream(music.second);
        }

    }

    SoundsManager::~SoundsManager()
    {

    }

    SoundsManager& SoundsManager::getInstance(void)
    {
        static SoundsManager instance;
        return instance;
    }


    std::unordered_map<SoundsManager::SongType, Sound>& SoundsManager::getSounds(void)
    {
        return _sounds;
    }

    std::unordered_map<SoundsManager::MusicType, Music>& SoundsManager::getMusics(void)
    {
        return _musics;
    }

}