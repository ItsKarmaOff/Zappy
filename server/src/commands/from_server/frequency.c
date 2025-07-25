/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
** the "frequency" command for server clients
*/
/**
 * @file frequency.c
 * @brief The file containing the handling of
 * the "frequency" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void change_frequency(server_t *server, char **args)
{
    size_t frequency = my_get_number(args[1], DEFAULT_NB);

    if (my_errno != SUCCESS || frequency == 0) {
        ERROR(my_create_str("Invalid frequency value: %zu", frequency));
        return;
    }
    server->game.game_settings.frequency = frequency;
    printf("Frequency set to: %zu\n", frequency);
}

void handle_server_command_frequency(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Frequency\" command");
    if (my_array_len((void **) args) != 1
    && my_array_len((void **) args) != 2) {
        ERROR("Invalid number of arguments for \"Frequency\" command");
        return;
    }
    if (my_array_len((void **) args) == 1) {
        printf("Current frequency: %s\n", args[1]);
        return;
    }
    change_frequency(server, args);
}
