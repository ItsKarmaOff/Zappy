/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
 * the "infinite_food" command for server clients
*/
/**
 * @file infinite_food.c
 * @brief The file containing the handling of
 * the "Infinite Food" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_infinite_food(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Infinite Food\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Infinite Food\" command");
        return;
    }
    if (server->game.game_settings.infinite_food == false) {
        server->game.game_settings.infinite_food = true;
        printf(GREEN "Infinite food has been enabled." ENDL);
    } else {
        server->game.game_settings.infinite_food = false;
        printf(RED "Infinite food has been disabled." ENDL);
    }
}
