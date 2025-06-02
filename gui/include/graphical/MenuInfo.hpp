/*
** EPITECH PROJECT, 2025
** MenuInfo.hpp
** File description:
** MenuInfo declaration
*/


#ifndef MENUINFO_HPP
    #define MENUINFO_HPP

    #include <raylib.h>

namespace Gui {

    class MenuInfo {
        public:
            MenuInfo();
            ~MenuInfo() = default;

            Rectangle &getPlayButton(void);
        private:
            Rectangle _playButton;

    };

}

#endif // GAMEINFO_HPP