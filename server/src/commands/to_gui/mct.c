/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "mct" command for GUI clients
*/
/**
 * @file mct.c
 * @brief The file containing the sending of
 * the "mct" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_mct_to_gui(server_t *server, client_t *client)
{
    for (size_t x = 0; x < server->game.game_settings.width; x++) {
        for (size_t y = 0; y < server->game.game_settings.height; y++)
            send_bct_to_gui(server, client, (vector2u_t){x, y});
    }
}
