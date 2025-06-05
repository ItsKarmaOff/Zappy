/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The network.h
*/
/**
 * @file network.h
 * @brief The network.h
 * @author Nicolas TORO
 */

#ifndef NETWORK_H_
    #define NETWORK_H_

    #include "game.h"
    #include "commands.h"

/* Initialization functions */

/**
 * @brief Configure and start the server
 * @param server The server to configure and start
 */
void start_server(server_t *server);



/* Polling functions */

/**
 * @brief Analyse the poll events for a specific client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void analyse_poll(server_t *server, size_t index);



/* Remove client functions */

/**
 * @brief Remove a client from the server
 * @param server The server containing the client
 * @param index The index of the client to remove
 */
void remove_client(server_t *server, size_t index);



/* Write client action functions */

/**
 * @brief Write the action of a client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void write_client_action(server_t *server, size_t index);



/* Read client action functions */

/**
 * @brief Read the action of a client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void read_client_action(server_t *server, size_t index);



/* Add new client functions */

/**
 * @brief Add a new client to the server
 * @param server The server to add the client to
 */
void add_new_client(server_t *server);



/* Get response functions */

/**
 * @brief Get the response from a client
 * @param socket_fd The file descriptor of the client socket
 * @return The response from the client
 */
char *get_response(int socket_fd);



/* Send message to GUI functions */

/**
 * @brief Send a message to all GUI clients
 * @param server The server containing the GUI clients
 * @param message The message to send
 */
void send_message_to_gui(server_t *server, const char *message);



/* Clients */

/**
 * @brief Create a new client
 * @return A pointer to the client
 */
void destroy_client(client_t *client);

#endif /* NETWORK_H_ */
