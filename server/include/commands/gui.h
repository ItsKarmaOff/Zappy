/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The gui.h
*/
/**
 * @file gui.h
 * @brief The gui.h
 * @author Nicolas TORO
 */

#ifndef GUI_H_
    #define GUI_H_

    #include "data_structures.h"

/**
 * @brief Handles the "msz" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_msz(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "bct" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_bct(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "mct" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_mct(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "tna" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_tna(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "ppo" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_ppo(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "plv" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_plv(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "pin" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_pin(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "sgt" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_sgt(server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "sst" command for GUI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_command_sst(server_t *server, client_t *client, char **args);

#endif /* GUI_H_ */
