/*
** EPITECH PROJECT, 2025
** SoundsManager.hpp
** File description:
** SoundsManager declaration
*/


#ifndef SOUNDSMANAGER_HPP
    #define SOUNDSMANAGER_HPP


    #include <raylib.h>
#include <unordered_map>

namespace Gui {
    class SoundsManager {
        public:
            enum SongType {
                MENU_SOUND,
                GAME_SOUND,
                PICKUP_SOUND,
            };

            enum MusicType {
                MENU_SONG,
                GAME_SONG,
            };

            SoundsManager();
            ~SoundsManager();

            static SoundsManager &getInstance(void);

            std::unordered_map<SongType, Sound> &getSounds(void);
            std::unordered_map<MusicType, Music> &getMusics(void);

        private:
            std::unordered_map<SongType, Sound> _sounds;
            std::unordered_map<MusicType, Music> _musics;

    };
}

#endif // SOUNDSMANAGER_HPP