/*
** EPITECH PROJECT, 2025
** MenuInfo.hpp
** File description:
** MenuInfo declaration
*/


#ifndef MENUINFO_HPP
    #define MENUINFO_HPP

    #include "Button.hpp"
    #include <raylib.h>
    #include <vector>

namespace Gui {
    class MenuInfo {
        public:
            enum ButtonIndex {
                PLAY_BUTTON,
                EXIT_BUTTON
            };
            MenuInfo();
            ~MenuInfo() = default;

            std::vector<Button> &getButtons();

        private:
            std::vector<Button> _buttons;

    };

}

#endif // GAMEINFO_HPP