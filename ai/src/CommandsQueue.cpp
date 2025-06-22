/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** CommandsQueue - Version basée sur le GUI (utilise std::vector<std::string>)
*/

#include "CommandsQueue.hpp"

CommandsQueue::CommandsQueue()
{
}

CommandsQueue::~CommandsQueue()
{
}

void CommandsQueue::pushCommand(const std::vector<std::string>& command)
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    _commandsQueue.push(command);
}

bool CommandsQueue::hasCommands() const
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    return !_commandsQueue.empty();
}

std::vector<std::string> CommandsQueue::popCommand()
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    if (_commandsQueue.empty())
        return {};
    std::vector<std::string> command = _commandsQueue.front();
    _commandsQueue.pop();
    return command;
}

void CommandsQueue::pushResponse(const std::string& response)
{
    std::lock_guard<std::mutex> lock(_responseQueueMutex);
    _responseQueue.push(response);
}

bool CommandsQueue::hasResponses() const
{
    std::lock_guard<std::mutex> lock(_responseQueueMutex);
    return !_responseQueue.empty();
}

std::string CommandsQueue::popResponse()
{
    std::lock_guard<std::mutex> lock(_responseQueueMutex);
    if (_responseQueue.empty())
        return "";
    std::string response = _responseQueue.front();
    _responseQueue.pop();
    return response;
}

void CommandsQueue::clearCommands()
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    while (!_commandsQueue.empty())
        _commandsQueue.pop();
}

void CommandsQueue::clearResponses()
{
    std::lock_guard<std::mutex> lock(_responseQueueMutex);
    while (!_responseQueue.empty())
        _responseQueue.pop();
}