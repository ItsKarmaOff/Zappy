/*
** EPITECH PROJECT, 2025
** Project
** File description:
** The server.h
*/
/**
 * @file server.h
 * @brief The server.h
 * @author Nicolas TORO
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
 * @brief Runs the server
 * @param server The server instance to run
 * @throw FAILURE If the server fails to run
 */
void run(server_t *server);

#endif /* SERVER_H_ */
