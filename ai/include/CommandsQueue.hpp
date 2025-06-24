/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** CommandsQueue
*/

#ifndef COMMANDSQUEUE_HPP_
#define COMMANDSQUEUE_HPP_

#include "Lib.hpp"

class CommandsQueue {
    public:
        CommandsQueue();
        ~CommandsQueue();
        void pushCommand(const std::string &command);
        bool hasCommands() const;
        std::string popCommand();
        void pushResponse(const std::string &response);
        bool hasResponses() const;
        std::string popResponse();
        void clearCommands();
        void clearResponses();
        void pushPendingCommand(const std::string& command);
        std::string getCurrentPendingCommand() const;
        void popPendingCommand();
        bool hasPendingCommand() const;
        void clearPendingCommands();

    protected:
    private:
        std::queue<std::string> _pendingCommands;
        mutable std::mutex _pendingMutex;
        std::queue<std::string> _commandsQueue;
        std::queue<std::string> _responsesQueue;
        mutable std::mutex _commandsQueueMutex;
        mutable std::mutex _responsesQueueMutex;
};

#endif /* !COMMANDSQUEUE_HPP_ */