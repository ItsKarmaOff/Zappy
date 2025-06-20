/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The infinite_food.c
*/
/**
 * @file infinite_food.c
 * @brief The infinite_food.c
 * @author Nicolas TORO
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
