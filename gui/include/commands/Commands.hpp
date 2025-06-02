/*
** EPITECH PROJECT, 2025
** Commands.hpp
** File description:
** Commands declaration
*/

#ifndef COMMANDS_HPP
    #define COMMANDS_HPP

    #include <string>
    #include <vector>

namespace Gui
{
    class Commands {
        public:

        //////////////////// Constructors and Destructor ///////////////////////

            /**
             * @brief Construct a new Commands object.
             */
            Commands() = default;

            /**
             * @brief Destroy the Commands object.
             */
            ~Commands() = default;



        //////////////////// Main Methods //////////////////////////////////////

        /**
         * @brief Handle a command.
         */
        void handleCommand();
    };
}

#endif /* !COMMANDS_HPP */
