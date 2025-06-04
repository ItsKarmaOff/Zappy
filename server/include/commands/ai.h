/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The ai.h
*/
/**
 * @file ai.h
 * @brief The ai.h
 * @author Nicolas TORO
 */

#ifndef AI_H_
    #define AI_H_

    #include "data_structures.h"

/**
 * @brief Handles the "Forward" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_forward(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Right" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_right(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Left" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_left(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Look" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_look(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Inventory" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_inventory(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Broadcast" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_broadcast(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Connect_nbr" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_connect_nbr(server_t *server, client_t *client,
    char **args);

/**
 * @brief Handles the "Fork" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_fork(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Eject" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_eject(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Take" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_take(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Set" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_set(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Incantation" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_incantation(server_t *server, client_t *client,
    char **args);

#endif /* AI_H_ */
