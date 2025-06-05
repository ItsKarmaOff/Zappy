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

void destroy_client(client_t *client)
{
    FREE(client->player);
    my_delete_list(&client->command_queue);
    FREE(client);
}
