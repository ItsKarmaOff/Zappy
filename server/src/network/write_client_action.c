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

const command_t commands_ai[] = {
    {"Forward", 7, &handle_command_forward},
    {"Right", 7, &handle_command_right},
    {"Left", 7, &handle_command_left},
    {"Look", 7, &handle_command_look},
    {"Inventory", 1, &handle_command_inventory},
    {"Broadcast", 7, &handle_command_broadcast},
    {"Connect_nbr", 0, &handle_command_connect_nbr},
    {"Fork", 42, &handle_command_fork},
    {"Eject", 7, &handle_command_eject},
    {"Take", 7, &handle_command_take},
    {"Set", 7, &handle_command_set},
    {"Incantation", 300, &handle_command_incantation},
    {NULL, 0, NULL}
};

const command_t commands_gui[] = {
    {"msz", 0, &handle_command_msz},
    {"bct", 0, &handle_command_bct},
    {"mct", 0, &handle_command_mct},
    {"tna", 0, &handle_command_tna},
    {"ppo", 0, &handle_command_ppo},
    {"plv", 0, &handle_command_plv},
    {"pin", 0, &handle_command_pin},
    {"sgt", 0, &handle_command_sgt},
    {"sst", 0, &handle_command_sst},
    {NULL, 0, NULL}
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

static bool set_next_action(server_t *server, size_t index,
    char *command, char **args)
{
    const command_t *commands = server->client_list[index - 1]->is_gui ?
        commands_gui : commands_ai;

    for (size_t cmd = 0; commands[cmd].command != NULL; cmd++) {
        if (my_strcmp(args[0], commands[cmd].command) == 0) {
            server->client_list[index - 1]->next_action.action_args = args;
            server->client_list[index - 1]->next_action.time_to_wait =
                commands[cmd].time_to_wait;
            server->client_list[index - 1]->next_action.cmd_function =
                commands[cmd].cmd_function;
            server->client_list[index - 1]->last_action_time = time(NULL);
            FREE(command);
            return true;
        }
    }
    return false;
}

static void write_action(server_t *server, size_t index)
{
    char *command = get_next_command(server, index - 1);
    char **args = MA(FALSE,
        my_str_to_word_array, command, " \t\n", LIST_SEPARATOR);

    my_update_malloc(TRUE);
    if (IS_NULL(args) || IS_NULL(args[0]) || IS_NULL(command)) {
        FREE(command);
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_AI);
        return;
    }
    DEBUG(my_create_str("Client %zu: receive command: %S\n", index + 1, args));
    if (set_next_action(server, index, command, args))
        return;
    ERROR(my_create_str("Unknown command: %s\n", args[0]));
    if (server->client_list[index - 1]->is_gui == true)
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_GUI);
    else
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_AI);
    FREE(command);
    FREE_WORD_ARRAY(args);
}

void write_client_action(server_t *server, size_t index)
{
    size_t command_count = 0;

    if (server->client_list[index - 1]->next_action.cmd_function != NULL)
        return;
    for (node_t *tmp = server->client_list[index - 1]->command_queue;
    tmp != NULL; tmp = tmp->next)
        command_count += my_count_letter(tmp->data, '\n');
    if (command_count <= 1)
        server->poll_fds[index].events &= ~POLLOUT;
    return write_action(server, index);
}
