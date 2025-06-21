/*
** EPITECH PROJECT, 2025
** QueueManager.cpp
** File description:
** QueueManager in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/core
*/
/**
 * @file QueueManager.cpp
 * @brief QueueManager implementation for the GUI
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "QueueManager.hpp"

namespace Gui
{
    //////////////////////// Commands queue methods ////////////////////////////

    void QueueManager::pushCommand(const std::vector<std::string>& command) {
        std::lock_guard<std::mutex> lock(_commandsQueueMutex);
        _commandsQueue.push(command);
    }

    bool QueueManager::hasCommands() const {
        std::lock_guard<std::mutex> lock(_commandsQueueMutex);
        return !_commandsQueue.empty();
    }

    std::vector<std::string> QueueManager::popCommand() {
        std::lock_guard<std::mutex> lock(_commandsQueueMutex);
        if (_commandsQueue.empty())
            return {};
        auto command = _commandsQueue.front();
        _commandsQueue.pop();
        return command;
    }



    //////////////////////// Response queue methods ////////////////////////////

    void QueueManager::pushResponse(const std::string& response) {
        std::lock_guard<std::mutex> lock(_responseQueueMutex);
        _responseQueue.push(response);
    }

    bool QueueManager::hasResponses() const {
        std::lock_guard<std::mutex> lock(_responseQueueMutex);
        return !_responseQueue.empty();
    }

    std::string QueueManager::popResponse() {
        std::lock_guard<std::mutex> lock(_responseQueueMutex);
        if (_responseQueue.empty())
            return "";
        auto response = _responseQueue.front();
        _responseQueue.pop();
        return response;
    }
}