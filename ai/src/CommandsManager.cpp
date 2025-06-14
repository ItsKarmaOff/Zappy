/*
** EPITECH PROJECT, 2025
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** Commands
*/

#include "CommandsManager.hpp"

CommandsManager::CommandsManager(std::shared_ptr<Lib::Socket> clientSocket, std::shared_ptr<CommandsQueue> commandsQueue)
    : _clientSocket(clientSocket), _queue(commandsQueue)
{
}

CommandsManager::~CommandsManager()
{
}

void CommandsManager::broadcast(const std::string &message)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Broadcast " + message + "\n";
    _queue->pushCommand(command);
}

void CommandsManager::eject()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Eject\n";
    _queue->pushCommand(command);
}

void CommandsManager::fork()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Fork\n";
    _queue->pushCommand(command);
}

void CommandsManager::inventory()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Inventory\n";
    _queue->pushCommand(command);
}

void CommandsManager::look()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Look\n";
    _queue->pushCommand(command);
}

void CommandsManager::forward()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Forward\n";
    _queue->pushCommand(command);
}

void CommandsManager::right()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Right\n";
    _queue->pushCommand(command);
}

void CommandsManager::left()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Left\n";
    _queue->pushCommand(command);
}

void CommandsManager::connect_nbr()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Connect_nbr\n";
    _queue->pushCommand(command);
}

void CommandsManager::take(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Take " + item + "\n";
    _queue->pushCommand(command);
}

void CommandsManager::set(const std::string &item)
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Set " + item + "\n";
    _queue->pushCommand(command);
}

void CommandsManager::incantation()
{
    if (!_clientSocket) {
        throw Lib::Exceptions::Warning("Client socket is not initialized.");
    }
    std::string command = "Incantation\n";
    _queue->pushCommand(command);
}