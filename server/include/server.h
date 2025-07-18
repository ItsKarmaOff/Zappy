/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The server class declaration
*/
/**
 * @file server.h
 * @brief The server class declaration
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef SERVER_H_
    #define SERVER_H_

    #include "parsing.h"
    #include "network.h"

/**
 * @brief Creates a server instance
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return A pointer to the created server instance
 * @throw FAILURE If the server creation fails
 */
server_t *create_server(int argc, char **argv);

/**
 * @brief Displays the server information
 * @param server The server instance to display
 * @param display_details Whether to display detailed information
 */
void display_server(const server_t *server, bool display_details);

/**
 * @brief Runs the server
 * @param server The server instance to run
 * @throw FAILURE If the server fails to run
 */
void run(server_t *server);

#endif /* SERVER_H_ */
