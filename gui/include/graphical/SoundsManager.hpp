/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The SoundsManager class declaration
*/
/**
 * @file SoundsManager.hpp
 * @brief The SoundsManager class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef SOUNDSMANAGER_HPP
    #define SOUNDSMANAGER_HPP

    #include "Lib.hpp"
    #include <raylib.h>
    #include <raymath.h>

namespace Gui
{
    class SoundsManager {
        public:

            //////////////// Enumerations //////////////////////////////////////

            enum SongType {
                MENU_SOUND,
                GAME_SOUND,
                PICKUP_SOUND,
            };

            enum MusicType {
                MENU_SONG,
                GAME_SONG,
            };



            //////////////// Constructors and Destructor ///////////////////////

            SoundsManager();
            ~SoundsManager();



            //////////////// Getters ///////////////////////////////////////////

            static SoundsManager &getInstance(void);
            std::unordered_map<SongType, Sound> &getSounds(void);
            std::unordered_map<MusicType, Music> &getMusics(void);

        private:
            std::unordered_map<SongType, Sound> _sounds;
            std::unordered_map<MusicType, Music> _musics;
    };
}

#endif // SOUNDSMANAGER_HPP