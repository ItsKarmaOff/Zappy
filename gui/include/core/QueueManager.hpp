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

namespace Gui {
    class QueueManager {
    public:
        QueueManager() = default;
        ~QueueManager() = default;

        // Commands queue methods
        void pushCommand(const std::vector<std::string>& command);
        bool hasCommands() const;
        std::vector<std::string> popCommand();

        // Response queue methods
        void pushResponse(const std::string& response);
        bool hasResponses() const;
        std::string popResponse();

    private:
        mutable std::mutex _commandsQueueMutex;
        std::queue<std::vector<std::string>> _commandsQueue;

        mutable std::mutex _responseQueueMutex;
        std::queue<std::string> _responseQueue;
    };
}

#endif // QUEUEMANAGER_HPP