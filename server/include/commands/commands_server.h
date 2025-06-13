/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The commands_server.h
*/
/**
 * @file commands_server.h
 * @brief The commands_server.h
 * @author Nicolas TORO
 */

#ifndef COMMANDS_SERVER_H_
    #define COMMANDS_SERVER_H_

    #include "server.h"

/* Command handler functions for server clients */

/**
 * @brief Handles the "help" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_help(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "status" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_status(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Debug Mode" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_debug_mode(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Extra Logs" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_extra_logs(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Clear" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_clear(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Quit" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_quit(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Clients" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_clients(server_t *server, UNUSED client_t *client,
    char **args);

/**
 * @brief Handles the "Client" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_client(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Kick" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_kick(server_t *server, UNUSED client_t *client,
    char **args);

#endif /* COMMANDS_SERVER_H_ */
