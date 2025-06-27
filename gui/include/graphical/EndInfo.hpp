/*
** EPITECH PROJECT, 2025
** EndInfo.hpp
** File description:
** EndInfo declaration
*/


#ifndef ENDINFO_HPP
    #define ENDINFO_HPP

/**
 * @file EndInfo.hpp
 * @brief Contains the EndInfo class for managing end scene information
 * @author Gianni TUERO
 */

#include "Button.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>
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
                RESTART,        ///< Button to restart the game
                EXIT     ///< Button to quit the game
            };
            /**
             * @brief Default constructor for EndInfo
             */
            EndInfo();

            /**
             * @brief Default destructor for EndInfo
             */
            ~EndInfo() = default;
        public:
            std::string winner; ///< Name of the winning team
            Color teamColor;   ///< Color of the winning team
            std::unordered_map<ButtonType, Button> buttons; ///< Buttons for the end scene

    };

}

#endif // ENDINFO_HPP