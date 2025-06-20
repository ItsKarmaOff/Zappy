/*
** EPITECH PROJECT, 2025
** QueueManager.hpp
** File description:
** QueueManager declaration
*/


#ifndef QUEUEMANAGER_HPP
    #define QUEUEMANAGER_HPP

#include <queue>
#include <string>
#include <vector>
#include <mutex>

/**
 * @file QueueManager.hpp
 * @brief The QueueManager class
 * @author Gianni TUERO
 */

namespace Gui {
    /**
     * @class QueueManager
     * @brief Manages queues for commands and responses with thread-safety
     */
    class QueueManager {
    public:
        /**
         * @brief Default constructor
         */
        QueueManager() = default;

        /**
         * @brief Default destructor
         */
        ~QueueManager() = default;

        // Commands queue methods

        /**
         * @brief Adds a command to the commands queue
         * @param command Vector of strings representing the command and its arguments
         */
        void pushCommand(const std::vector<std::string>& command);

        /**
         * @brief Checks if there are commands in the queue
         * @return True if the commands queue is not empty, false otherwise
         */
        bool hasCommands() const;

        /**
         * @brief Retrieves and removes the first command from the queue
         * @return Vector of strings representing the command and its arguments
         */
        std::vector<std::string> popCommand();

        // Response queue methods

        /**
         * @brief Adds a response to the responses queue
         * @param response String representing the response
         */
        void pushResponse(const std::string& response);

        /**
         * @brief Checks if there are responses in the queue
         * @return True if the responses queue is not empty, false otherwise
         */
        bool hasResponses() const;

        /**
         * @brief Retrieves and removes the first response from the queue
         * @return String representing the response
         */
        std::string popResponse();

    private:
        mutable std::mutex _commandsQueueMutex; //< Mutex for thread-safe access to the commands queue
        std::queue<std::vector<std::string>> _commandsQueue; //< Queue for commands
        mutable std::mutex _responseQueueMutex; //< Mutex for thread-safe access to the responses queue
        std::queue<std::string> _responseQueue; //< Queue for responses
    };
}

#endif // QUEUEMANAGER_HPP