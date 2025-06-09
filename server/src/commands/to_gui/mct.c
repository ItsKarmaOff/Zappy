/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The mct.c
*/
/**
 * @file mct.c
 * @brief The mct.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_mct_to_gui(server_t *server)
{
    for (size_t x = 0; x < server->game.game_settings.width; x++) {
        for (size_t y = 0; y < server->game.game_settings.height; y++)
            send_bct_to_gui(server, (vector2u_t){x, y});
    }
}
