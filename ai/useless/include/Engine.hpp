/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Engine class implementation
*/
/**
 * @file Engine.hpp
 * @brief The Engine class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef ENGINE_HPP_
    #define ENGINE_HPP_

    #include "Parser.hpp"
    #include "Player.hpp"

/**
 * @class Engine
 * @brief Main engine class for managing the Zappy AI client
 */
class Engine {
    public:
        /**
         * @brief Constructor for Engine
         * @param parser Reference to the parser containing configuration
         */
        Engine(Parser &parser);

        /**
         * @brief Destructor for Engine
         */
        ~Engine();

        /**
         * @brief Main execution loop for the engine
         */
        void run();

        /**
         * @brief Get response from the server socket
         * @param socket Pointer to the socket to read from
         * @return The response string from the server
         */
        std::string getResponse(Lib::Socket *socket);

    protected:

    private:
        /**
         * @brief Initialize the engine and connect to server
         */
        void _init();

        /**
         * @brief Create a new player instance for forked processes
         */
        void _createNewPlayer();

        /**
         * @brief Handle communication with the server
         * @param clientSocket Pointer to the client socket
         */
        void _communicate(Lib::Socket *clientSocket);

        /**
         * @brief Read response from server if available
         * @param socket Pointer to the socket to read from
         */
        void _readIfResponse(Lib::Socket *socket);

        /**
         * @brief Send command to server if available
         * @param socket Pointer to the socket to send to
         */
        void _sendIfCommand(Lib::Socket *socket);

        Parser &_parser; ///< Reference to command line parser
        std::unique_ptr<Lib::Socket> _socket; ///< Socket for server communication
        struct sockaddr_in _client; ///< Client socket address structure
        std::shared_ptr<Player> _player; ///< Shared pointer to the player instance
        struct pollfd _pollFd; ///< Poll file descriptor for socket monitoring
        int _amountOfPlayers; ///< Number of players to create
        bool _isRunning; ///< Flag indicating if engine is running
        std::vector<pid_t> _processes; ///< Vector of forked process IDs
};

#endif /* !ENGINE_HPP_ */
