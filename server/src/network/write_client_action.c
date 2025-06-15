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
    {"Forward", 7, &handle_ai_command_forward},
    {"Right", 7, &handle_ai_command_right},
    {"Left", 7, &handle_ai_command_left},
    {"Look", 7, &handle_ai_command_look},
    {"Inventory", 1, &handle_ai_command_inventory},
    {"Broadcast", 7, &handle_ai_command_broadcast},
    {"Connect_nbr", 0, &handle_ai_command_connect_nbr},
    {"Fork", 42, &handle_ai_command_fork},
    {"Eject", 7, &handle_ai_command_eject},
    {"Take", 7, &handle_ai_command_take},
    {"Set", 7, &handle_ai_command_set},
    {"Incantation", 300, &handle_ai_command_incantation},
    {NULL, 0, NULL}
};

const command_t commands_gui[] = {
    {"msz", 0, &handle_gui_command_msz},
    {"bct", 0, &handle_gui_command_bct},
    {"mct", 0, &handle_gui_command_mct},
    {"tna", 0, &handle_gui_command_tna},
    {"ppo", 0, &handle_gui_command_ppo},
    {"plv", 0, &handle_gui_command_plv},
    {"pin", 0, &handle_gui_command_pin},
    {"sgt", 0, &handle_gui_command_sgt},
    {"sst", 0, &handle_gui_command_sst},
    {NULL, 0, NULL}
};

const command_t commands_server[] = {
    {"/all", 0, &handle_server_command_all},
    {"/broadcast", 0, &handle_server_command_broadcast},
    {"/clear", 0, &handle_server_command_clear},
    {"/client", 0, &handle_server_command_client},
    {"/clients", 0, &handle_server_command_clients},
    {"/debug_mode", 0, &handle_server_command_debug_mode},
    {"/extra_logs", 0, &handle_server_command_extra_logs},
    {"/fork", 0, &handle_server_command_fork},
    {"/frequency", 0, &handle_server_command_frequency},
    {"/help", 0, &handle_server_command_help},
    {"/infinite_food", 0, &handle_server_command_infinite_food},
    {"/inventory", 0, &handle_server_command_inventory},
    {"/kick", 0, &handle_server_command_kick},
    {"/level", 0, &handle_server_command_level},
    {"/map", 0, &handle_server_command_map},
    {"/no_refill", 0, &handle_server_command_no_refill},
    {"/orientation", 0, &handle_server_command_orientation},
    {"/pause", 0, &handle_server_command_pause},
    {"/player", 0, &handle_server_command_player},
    {"/players", 0, &handle_server_command_players},
    {"/quit", 0, &handle_server_command_quit},
    {"/send_ai", 0, &handle_server_command_send_ai},
    {"/send_gui", 0, &handle_server_command_send_gui},
    {"/status", 0, &handle_server_command_status},
    {"/team", 0, &handle_server_command_team},
    {"/teams", 0, &handle_server_command_teams},
    {"/tile", 0, &handle_server_command_tile},
    {"/tp", 0, &handle_server_command_tp},
};

const command_t *commands[] = {
    commands_ai,
    commands_gui,
    commands_server,
    NULL
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
    const command_t *selected_commands = commands[
        server->client_list[index - 1]->client_type];

    for (size_t cmd = 0; selected_commands[cmd].command != NULL; cmd++) {
        if (my_strcmp(args[0], selected_commands[cmd].command) == 0) {
            server->client_list[index - 1]->next_action.action_args = args;
            server->client_list[index - 1]->next_action.time_to_wait =
                selected_commands[cmd].time_to_wait;
            server->client_list[index - 1]->next_action.cmd_function =
                selected_commands[cmd].cmd_function;
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
    DEBUG(my_create_str("Client %zu: receive command: %S", index - 1, args));
    if (set_next_action(server, index, command, args))
        return;
    ERROR(my_create_str("Unknown command: %s", args[0]));
    if (server->client_list[index - 1]->client_type == CLIENT_AI)
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_AI);
    else if (server->client_list[index - 1]->client_type == CLIENT_GUI)
        dprintf(server->client_list[index - 1]->socket_fd, WRONG_GUI);
    FREE(command);
    FREE_WORD_ARRAY(args);
}

void write_client_action(server_t *server, size_t index)
{
    size_t command_count = 0;

    if (server->client_list[index - 1]->is_authenticated == false)
        return authenticate_client(server, index);
    if (server->client_list[index - 1]->next_action.cmd_function != NULL)
        return;
    for (node_t *tmp = server->client_list[index - 1]->command_queue;
    tmp != NULL; tmp = tmp->next)
        command_count += my_count_letter(tmp->data, '\n');
    if (command_count <= 1)
        server->poll_fds[index].events &= ~POLLOUT;
    return write_action(server, index);
}
