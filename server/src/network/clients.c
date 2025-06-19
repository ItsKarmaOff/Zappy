/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The clients.c
*/
/**
 * @file clients.c
 * @brief The clients.c
 * @author Nicolas TORO
 */

#include "network.h"

void destroy_client(server_t *server, client_t *client)
{
    FREE(client->team_name);
    if (client->player != NULL) {
        send_pdi_to_gui(server, NULL, client->player);
        my_delete_nodes(&client->player->team->player_list,
            client->player, NULL);
    }
    my_delete_list(&client->command_queue);
    FREE_WORD_ARRAY(client->next_action.action_args);
    FREE(client);
}

void destroy_clients(server_t *server)
{
    for (size_t index = 1; index < server->current_clients_number + 1;
    index++) {
        close(server->poll_fds[index].fd);
        destroy_client(server, server->client_list[index - 1]);
    }
    FREE(server->poll_fds);
    FREE(server->client_list);
}

void resize_client_list(server_t *server, size_t new_size)
{
    server->poll_fds = AL(FALSE, my_resize_alloc, server->poll_fds,
        sizeof(pollfd_t) * (server->current_clients_number + 1),
        sizeof(pollfd_t) * (new_size + 1));
    server->client_list = AL(FALSE, my_resize_alloc, server->client_list,
        sizeof(client_t *) * (server->current_clients_number),
        sizeof(client_t *) * new_size);
    server->current_clients_number = new_size;
}

size_t get_client_index(const server_t *server, client_t *client)
{
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index] == client)
            return index + 1;
    }
    return 0;
}
