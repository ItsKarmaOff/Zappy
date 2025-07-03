/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** The CommandsQueue implementation
** CommandsQueue
*/
/**
 * @file CommandsQueue.cpp
 * @brief The CommandsQueue implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "CommandsQueue.hpp"

CommandsQueue::CommandsQueue() {
}

CommandsQueue::~CommandsQueue() {
}

void CommandsQueue::pushCommand(const std::string& command) {
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    _commandsQueue.push(command);
}

bool CommandsQueue::hasCommands() const {
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    return !_commandsQueue.empty();
}

std::string CommandsQueue::popCommand() {
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    if (_commandsQueue.empty())
        return "";
    std::string command = _commandsQueue.front();
    _commandsQueue.pop();
    return command;
}

void CommandsQueue::pushResponse(const std::string& response) {
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    _responsesQueue.push(response);
}

bool CommandsQueue::hasResponses() const {
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    return !_responsesQueue.empty();
}

std::string CommandsQueue::popResponse() {
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    if (_responsesQueue.empty())
        return "";
    std::string response = _responsesQueue.front();
    _responsesQueue.pop();
    return response;
}

void CommandsQueue::clearCommands() {
    std::lock_guard<std::mutex> lock(_commandsQueueMutex);
    while (!_commandsQueue.empty())
        _commandsQueue.pop();
}

void CommandsQueue::clearResponses() {
    std::lock_guard<std::mutex> lock(_responsesQueueMutex);
    while (!_responsesQueue.empty())
        _responsesQueue.pop();
}

void CommandsQueue::pushPendingCommand(const std::string& command) {
    std::lock_guard<std::mutex> lock(_pendingMutex);
    _pendingCommands.push(command);
}

std::string CommandsQueue::getCurrentPendingCommand() const {
    std::lock_guard<std::mutex> lock(_pendingMutex);
    if (_pendingCommands.empty())
        return "";
    return _pendingCommands.front();
}

void CommandsQueue::popPendingCommand() {
    std::lock_guard<std::mutex> lock(_pendingMutex);
    if (!_pendingCommands.empty())
        _pendingCommands.pop();
}

bool CommandsQueue::hasPendingCommand() const {
    std::lock_guard<std::mutex> lock(_pendingMutex);
    return !_pendingCommands.empty();
}

void CommandsQueue::clearPendingCommands() {
    std::lock_guard<std::mutex> lock(_pendingMutex);
    while (!_pendingCommands.empty())
        _pendingCommands.pop();
}