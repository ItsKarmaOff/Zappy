/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the network functions
*/
/**
 * @file network.h
 * @brief The file containing the network functions
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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

/**
 * @brief Get the IP address of the server
 * @return A string containing the IP address of the server
 */
char *get_ip_address(void);



/* Polling functions */

/**
 * @brief Analyse the poll events for a specific client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void analyze_poll(server_t *server, size_t index);



/* Remove client functions */

/**
 * @brief Remove a client from the server
 * @param server The server containing the client
 * @param index The index of the client to remove
 */
void remove_client(server_t *server, size_t index);



/* Write client functions */

/**
 * @brief Authenticate a client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void authenticate_client(server_t *server, size_t index);

/**
 * @brief Write the action of a client
 * @param server The server containing the client
 * @param index The index of the client in the poll_fds array
 */
void write_client_action(server_t *server, size_t index);



/* Read client functions */

/**
 * @brief Get the response from a client
 * @param socket_fd The file descriptor of the client socket
 * @return The response from the client
 */
char *get_response(int socket_fd);

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




/* Send message to GUI functions */

/**
 * @brief Send a message to all GUI clients
 * @param server The server containing the GUI clients
 * @param message The message to send
 */
void send_message_to_gui(server_t *server, const char *message);



/* Clients */

/**
 * @brief Destroy a client
 * @param server The server containing the client
 * @param client The client to destroy
 * @param is_closing Whether the server is closing
 * (to avoid sending messages to GUI)
 */
void destroy_client(server_t *server, client_t *client, bool is_closing);

/**
 * @brief Destroy all clients in the server
 * @param server The server containing the clients
 */
void destroy_clients(server_t *server);

/**
 * @brief Resize the client list
 * @param server The server containing the client list
 * @param new_size The new size of the client list
 */
void resize_client_list(server_t *server, size_t new_size);

/**
 * @brief Execute actions for all clients
 * @param server The server containing the clients
 */
void execute_actions(server_t *server);

/**
 * @brief Get the index of a client in the server's client list
 * @param server The server containing the client
 * @param client The client to find
 * @return The index of the client in the server's client list
 */
size_t get_client_index(const server_t *server, client_t *client);

#endif /* NETWORK_H_ */
