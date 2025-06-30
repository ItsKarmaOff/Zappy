/*
** EPITECH PROJECT, 2025
** Zappy
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
        std::mutex &getCommandsQueueMutex() const { return _commandsQueueMutex; }
        std::mutex &getResponsesQueueMutex() const { return _responsesQueueMutex; }
        std::condition_variable &getResponseCondition() { return _responseCondition; }

    protected:
    private:
        std::queue<std::string> _commandsQueue;
        std::queue<std::string> _responsesQueue;
        mutable std::mutex _commandsQueueMutex;
        mutable std::mutex _responsesQueueMutex;
        std::condition_variable _responseCondition;
};

#endif /* !COMMANDSQUEUE_HPP_ */
