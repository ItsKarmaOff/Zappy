/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Core class declaration
*/
/**
 * @file Core.hpp
 * @brief The Core class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef CORE_HPP
    #define CORE_HPP

    #include "Graphics.hpp"
    #include "QueueManager.hpp"
    #include "Parser.hpp"

namespace Gui
{
    /**
     * @class Core
     * @brief The Core class handles the main logic of the GUI application.
     */
    class Core {
        public:

            //////////////// Constructors and Destructor ///////////////////////

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



            //////////////// Main Methods //////////////////////////////////////

            /**
            * @brief Run the main loop of the GUI application.
            */
            void run();

            /**
			 * @brief Sends a command to the server
			 * @param fd The file descriptor of the socket
			 * @param command The command to send
			 */
            void sendCommand(int fd, const std::vector<std::string> &command);
            /**
             * @brief Receives a response from the server
             * @return The response from the server
             */
            std::string getResponse();

            /**
            * @brief readIfResponse checks if there is a response from the server and processes it.
            */
            void readIfResponse();

            /**
             * @brief sendIfCommand checks if there is a command to send and sends it to the server.
             */
            void sendIfCommand();



        private:

            //////////////// Private Methods ///////////////////////////////////

            /**
             * @brief Initialize the client socket and connect to the server.
             */
            void _initClient();

            /**
			 * @brief Thread for handling communication with the server
			 */
            void _communicationThread();

            /**
			 * @brief Thread for handling the game loop
			 */
            void _gameThread();

            /**
             * @brief manual allows the user to manually input commands in the console.
             */
            void manual();



            //////////////// Private Attributes ////////////////////////////////

            int _port; ///< The port number for the server connection
            std::string _hostname; ///< The hostname for the server connection
            std::unique_ptr<Lib::Socket> _clientSocket; ///< Pointer to the socket for communication with the server
            std::atomic<bool> isRunning; ///< Flag to indicate if the application is running
            struct sockaddr_in _client; ///< Structure to hold the client address information
            std::shared_ptr<QueueManager> _queueManager; ///< Shared pointer to the queue manager for handling commands and responses
            pollfd _pollFd; ///< Poll file descriptor for monitoring events on the socket
            std::string _answer; ///< String to hold the response from the server
    };
}

#endif /* !CORE_HPP */
