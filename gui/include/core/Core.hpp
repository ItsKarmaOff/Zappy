/*
** EPITECH PROJECT, 2025
** Core.hpp
** File description:
** Core declaration
*/

#ifndef CORE_HPP
    #define CORE_HPP

    #include <memory>
    #include <atomic>
    #include <string>
    #include "Graphics.hpp"
    #include "Socket.hpp"
    #include "QueueManager.hpp"

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



            //////////////// Getters ///////////////////////////////////////////

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



            //////////////// Setters ///////////////////////////////////////////

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



            //////////////// Utility Methods ///////////////////////////////////

            /**
            * @brief Print the usage of the program.
            */
            void printUsage() const;

        private:

            //////////////// Private Methods ///////////////////////////////////

            /**
            * @brief Parse the command line arguments.
            * @param argc The number of arguments
            * @param argv The arguments
            */
            void _parseArguments(int argc, char **argv);

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

            void manual();

            //////////////// Private Attributes ////////////////////////////////

            int _port;  // The port number for the server connection
            std::string _hostname;  // The hostname for the server connection
            std::unique_ptr<Lib::Socket> _clientSocket; // Pointer to the socket for communication with the server
            std::atomic<bool> isRunning;  // Flag to indicate if the application is running
            struct sockaddr_in _client; // Structure to hold the client address information
            std::shared_ptr<QueueManager> _queueManager; // Shared pointer to the queue manager for handling commands and responses
    };
}

#endif /* !CORE_HPP */
