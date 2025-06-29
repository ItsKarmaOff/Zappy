/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The SoundsManager class implementation
*/
/**
 * @file SoundsManager.cpp
 * @brief The SoundsManager class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "SoundsManager.hpp"

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