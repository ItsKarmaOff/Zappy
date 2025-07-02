/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The internal server commands
*/
/**
 * @file commands_server.h
 * @brief The internal server commands
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef COMMANDS_SERVER_H_
    #define COMMANDS_SERVER_H_

    #include "server.h"

/* Structure to hold command information */

/**
 * @struct command_help_s
 * @brief Structure to hold command information for server clients
 */
typedef struct command_help_s {
    /** The command name */
    const char *command;
    /** The command arguments */
    const char *args;
    /** The command description */
    const char *description;
} command_help_t;



/* Command handler functions for server clients */

/**
 * @brief Handles the "All" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_all(
    server_t *server, UNUSED client_t *client, char **args);

/**
 * @brief Handles the "Broadcast" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_broadcast(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "clear" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_clear(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "client" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_client(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "clients" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_clients(
    server_t *server, UNUSED client_t *client, char **args);

/**
 * @brief Handles the "debug mode" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_debug_mode(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "extra Logs" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_extra_logs(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "fork" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_fork(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "frequency" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_frequency(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "help" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_help(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "infinite food" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_infinite_food(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "inventory" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_inventory(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "kick" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_kick(
    server_t *server, UNUSED client_t *client, char **args);

/**
 * @brief Handles the "level" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_level(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "map" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_map(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "no refill" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_no_refill(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "orientation" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_orientation(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "pause" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_pause(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "player" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_player(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "players" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_players(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "quit" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_quit(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "send_ai" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_send_ai(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "send_gui" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_send_gui(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "status" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_status(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "team" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_team(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "teams" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_teams(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "tile" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_tile(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "tp" command for server clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_server_command_tp(
    server_t *server, client_t *client, char **args);

#endif /* COMMANDS_SERVER_H_ */
