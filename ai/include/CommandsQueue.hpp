/*
** EPITECH PROJECT, 2025
** Zappy
** B-YEP-400-NCE-4-1-zappy-nicolas.toro [WSL: Ubuntu]
** File description:
** The CommandsQueue class implementation
** CommandsQueue
*/
/**
 * @file CommandsQueue.hpp
 * @brief The CommandsQueue class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef COMMANDSQUEUE_HPP_
#define COMMANDSQUEUE_HPP_

#include "Lib.hpp"

/**
 * @class CommandsQueue
 * @brief Thread-safe queue system for managing commands and responses
 */
class CommandsQueue {
public:
    /**
     * @brief Constructor for CommandsQueue
     */
    CommandsQueue();
    
    /**
     * @brief Destructor for CommandsQueue
     */
    ~CommandsQueue();
    
    /**
     * @brief Push a command to the commands queue
     * @param command The command string to push
     */
    void pushCommand(const std::string &command);
    
    /**
     * @brief Check if there are commands in the queue
     * @return True if commands are available
     */
    bool hasCommands() const;
    
    /**
     * @brief Pop and return the next command from the queue
     * @return The next command string, empty if none available
     */
    std::string popCommand();
    
    /**
     * @brief Push a response to the responses queue
     * @param response The response string to push
     */
    void pushResponse(const std::string &response);
    
    /**
     * @brief Check if there are responses in the queue
     * @return True if responses are available
     */
    bool hasResponses() const;
    
    /**
     * @brief Pop and return the next response from the queue
     * @return The next response string, empty if none available
     */
    std::string popResponse();
    
    /**
     * @brief Clear all commands from the commands queue
     */
    void clearCommands();
    
    /**
     * @brief Clear all responses from the responses queue
     */
    void clearResponses();
    
    /**
     * @brief Push a command to the pending commands queue
     * @param command The command string to mark as pending
     */
    void pushPendingCommand(const std::string& command);
    
    /**
     * @brief Get the current pending command without removing it
     * @return The current pending command string, empty if none
     */
    std::string getCurrentPendingCommand() const;
    
    /**
     * @brief Remove the current pending command from the queue
     */
    void popPendingCommand();
    
    /**
     * @brief Check if there are pending commands
     * @return True if pending commands exist
     */
    bool hasPendingCommand() const;
    
    /**
     * @brief Clear all pending commands
     */
    void clearPendingCommands();

protected:

private:
    std::queue<std::string> _pendingCommands; ///< Queue for pending commands
    mutable std::mutex _pendingMutex; ///< Mutex for pending commands thread safety
    std::queue<std::string> _commandsQueue; ///< Queue for regular commands
    std::queue<std::string> _responsesQueue; ///< Queue for responses
    mutable std::mutex _commandsQueueMutex; ///< Mutex for commands queue thread safety
    mutable std::mutex _responsesQueueMutex; ///< Mutex for responses queue thread safety
};

#endif /* !COMMANDSQUEUE_HPP_ */