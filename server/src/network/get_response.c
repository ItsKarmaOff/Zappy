/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to get a response from a client
*/
/**
 * @file get_response.c
 * @brief The file containing the function to get a response from a client
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

static char *convert_data_to_string(node_t **data)
{
    char *response = NULL;
    size_t index = 0;

    response = AL(FALSE, my_calloc, my_list_size(*data) + 1, sizeof(char));
    for (node_t *node = *data; node != NULL; node = node->next) {
        response[index] = *(char *)node->data;
        index++;
    }
    my_delete_list(data);
    return response;
}

char *get_response(int socket_fd)
{
    node_t *data = NULL;
    char *tmp = NULL;
    ssize_t read_size = 0;

    while (true) {
        tmp = AL(FALSE, my_calloc, 1, sizeof(char));
        read_size = read(socket_fd, tmp, 1);
        if (read_size <= 0)
            THROW(my_create_str("EXCEPTION: Get response read data: %s",
                STRERR));
        if (tmp[0] == '\n')
            break;
        AL(FALSE, my_push_back, &data, tmp, STRING);
    }
    FREE(tmp);
    return convert_data_to_string(&data);
}
