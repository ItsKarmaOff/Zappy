/*
** EPITECH PROJECT, 2025
** Core.hpp
** File description:
** Core declaration
*/

#ifndef CORE_HPP
    #define CORE_HPP

    #include <string>

namespace gui
{
    /**
     * @class Core
     * @brief The Core class handles the main logic of the GUI application.
     */
    class Core {
        private:
            int _port;  // The port number for the server connection
            std::string _hostname;  // The hostname for the server connection

        public:

            // Constructors and Destructor

            /**
             * @brief Construct a new Core object.
             * @param argc The number of arguments
             * @param argv The arguments
             */
            Core(int argc, char **argv);

            /**
             * @brief Destroy the Core object.
             */
            ~Core() = default;


            // Parser

            /**
             * @brief Parse the command line arguments.
             * @param argc The number of arguments
             * @param argv The arguments
             */
            void parseArguments(int argc, char **argv);

            /**
             * @brief Print the usage of the program.
             */
            void printUsage() const;


            // Getters

            /**
             * @brief Get the port number.
             * @return The port number
             */
            int getPort() const;

            /**
             * @brief Get the hostname.
             * @return The hostname
             */
            const std::string &getHostname() const;


            // Setters

            /**
             * @brief Set the port number.
             * @param port The port number
             */
            void setPort(int port);

            /**
             * @brief Set the hostname.
             * @param hostname The hostname
             */
            void setHostname(const std::string &hostname);
    };
}

#endif /* !CORE_HPP */
