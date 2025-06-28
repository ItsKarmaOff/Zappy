/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The MenuInfo class declaration
*/
/**
 * @file MenuInfo.hpp
 * @brief The MenuInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */


#ifndef MENUINFO_HPP
    #define MENUINFO_HPP

    #include "Button.hpp"

/**
 * @file MenuInfo.hpp
 * @brief The MenuInfo class for managing menu buttons and interactions
 * @author Gianni TUERO
 */

namespace Gui {
    class MenuInfo {
        public:
            enum ButtonIndex {
                PLAY_BUTTON,
                EXIT_BUTTON
            };
            MenuInfo();
            ~MenuInfo() = default;

            /**
             * @brief Gets the reference to the buttons in the menu
             * @return Reference to the vector of Button objects
             */
            std::vector<Button> &getButtons();

        private:
            std::vector<Button> _buttons; ///< Vector containing all buttons in the menu
    };
}

#endif // GAMEINFO_HPP