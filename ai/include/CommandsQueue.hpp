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
        void pushCommand(const std::vector<std::string> &command);
        bool hasCommands() const;
        std::vector<std::string> popCommand();
        void pushResponse(const std::string &response);
        bool hasResponses() const;
        std::string popResponse();
        void clearCommands();
        void clearResponses();

    protected:
    private:
        std::queue<std::vector<std::string>> _commandsQueue;
        std::queue<std::string> _responseQueue;
        mutable std::mutex _commandsQueueMutex;
        mutable std::mutex _responseQueueMutex;
};

#endif /* !COMMANDSQUEUE_HPP_ */