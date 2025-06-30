/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** CommandsQueue
*/

#include "CommandsQueue.hpp"

CommandsQueue::CommandsQueue()
{
}

CommandsQueue::~CommandsQueue()
{
}

void CommandsQueue::pushCommand(const std::string& command)
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    _commandsQueue.push(command);
}

bool CommandsQueue::hasCommands() const
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    return !_commandsQueue.empty();
}

std::string CommandsQueue::popCommand()
{
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    if (_commandsQueue.empty())
        return {};
    std::string command = _commandsQueue.front();
    _commandsQueue.pop();
    return command;
}

void CommandsQueue::pushResponse(const std::string& response)
{
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    _responsesQueue.push(response);
}

bool CommandsQueue::hasResponses() const
{
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    return !_responsesQueue.empty();
}

std::string CommandsQueue::popResponse()
{
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    if (_responsesQueue.empty())
        return {};
    std::string response = _responsesQueue.front();
    _responsesQueue.pop();
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
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    while (!_responsesQueue.empty())
        _responsesQueue.pop();
}
