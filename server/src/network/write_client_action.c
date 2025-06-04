/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The write_client_action.c
*/
/**
 * @file write_client_action.c
 * @brief The write_client_action.c
 * @author Nicolas TORO
 */

#include "network.h"

const command_t commands[] = {
    /* AI commands */
    {"Forward", false, &handle_command_forward},
    {"Right", false, &handle_command_right},
    {"Left", false, &handle_command_left},
    {"Look", false, &handle_command_look},
    {"Inventory", false, &handle_command_inventory},
    {"Broadcast", false, &handle_command_broadcast},
    {"Connect_nbr", false, &handle_command_connect_nbr},
    {"Fork", false, &handle_command_fork},
    {"Eject", false, &handle_command_eject},
    {"Take", false, &handle_command_take},
    {"Set", false, &handle_command_set},
    {"Incantation", false, &handle_command_incantation},

    /* GUI commands */
    {"msz", true, &handle_command_msz},
    {"bct", true, &handle_command_bct},
    {"mct", true, &handle_command_mct},
    {"tna", true, &handle_command_tna},
    {"ppo", true, &handle_command_ppo},
    {"plv", true, &handle_command_plv},
    {"pin", true, &handle_command_pin},
    {"sgt", true, &handle_command_sgt},
    {"sst", true, &handle_command_sst},

    /* END */
    {NULL, false, NULL}
};

static size_t get_next_command_size(server_t *server, size_t index)
{
    size_t total_size = 1;

    for (node_t *command = server->client_list[index]->command_queue;
        command != NULL; command = command->next) {
        if (my_str_contains(command->data, "\n")) {
            total_size += my_strstr(command->data, "\n")
                - (char *) command->data;
            break;
        } else
            total_size += strlen(command->data);
    }
    return total_size;
}

static bool add_command_to_str(client_t *client, node_t *command,
    char *next_command, size_t *command_index)
{
    size_t command_size = 0;
    char *tmp = NULL;

    if (my_str_contains(command->data, "\n")) {
        command_size = my_strstr(command->data, "\n") - (char *)command->data;
        my_strncpy(next_command + *command_index, command->data, command_size);
        *command_index += command_size;
        tmp = AL(FALSE, my_strdup, my_strstr(command->data, "\n") + 1);
        FREE(command->data);
        command->data = tmp;
        return true;
    } else {
        command_size = strlen(command->data);
        my_strncpy(next_command + *command_index, command->data, command_size);
        *command_index += command_size;
        FREE(command->data);
        my_free_ptr(my_pop_front(&client->command_queue));
        return false;
    }
}

static char *get_next_command(server_t *server, size_t index)
{
    size_t total_size = get_next_command_size(server, index);
    char *next_command = NULL;
    size_t command_index = 0;

    next_command = AL(FALSE, my_calloc, total_size, sizeof(char));
    for (node_t *command = server->client_list[index]->command_queue;
    command != NULL; command = server->client_list[index]->command_queue) {
        if (add_command_to_str(server->client_list[index], command,
        next_command, &command_index))
            return next_command;
    }
    return next_command;
}

static bool execute_command(server_t *server, size_t index,
    char *command, char **args)
{
    for (size_t cmd = 0; commands[cmd].command != NULL; cmd++) {
        if (my_strcmp(args[0], commands[cmd].command) == 0
        && server->client_list[index - 1]->is_gui == commands[cmd].is_gui) {
            commands[cmd].cmd_function(
                server, server->client_list[index - 1], args);
            FREE(command);
            my_free_array((void **)args);
            return true;
        }
    }
    return false;
}

void write_client_action(server_t *server, size_t index)
{
    char *command = get_next_command(server, index - 1);
    char **args = MA(FALSE,
        my_str_to_word_array, command, " \t\n", LIST_SEPARATOR);

    my_update_malloc(TRUE);
    server->poll_fds[index].events &= ~POLLOUT;
    if (IS_NULL(args)) {
        FREE(command);
        return;
    }
    DEBUG(my_create_str("Processing command: %S\n", args));
    if (execute_command(server, index, command, args))
        return;
    DEBUG(my_create_str("Unknown command: %s\n", args[0]));
    if (server->client_list[index - 1]->is_gui == true)
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_GUI);
    else
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_AI);
    FREE(command);
    my_free_array((void **)args);
}
