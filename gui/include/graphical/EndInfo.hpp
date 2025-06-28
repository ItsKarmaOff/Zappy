/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The EndInfo class declaration
*/
/**
 * @file EndInfo.hpp
 * @brief The EndInfo class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef ENDINFO_HPP
    #define ENDINFO_HPP

    #include "Button.hpp"

namespace Gui {
    /**
     * @class EndInfo
     * @brief Contains information and methods related to the end scene of the game
     */
    class EndInfo {
        public:
            /**
             * @enum ButtonType
             * @brief Types of buttons available in the end scene
             */
            enum ButtonType {
                RESTART, ///< Button to restart the game
                EXIT ///< Button to quit the game
            };

            /**
             * @brief Default constructor for EndInfo
             */
            EndInfo();

            /**
             * @brief Default destructor for EndInfo
             */
            ~EndInfo() = default;



            //////////////// Public Attributes ////////////////////////////////

            std::string winner; ///< Name of the winning team
            Color teamColor; ///< Color of the winning team
            std::unordered_map<ButtonType, Button> buttons; ///< Buttons for the end scene
    };
}

#endif // ENDINFO_HPP