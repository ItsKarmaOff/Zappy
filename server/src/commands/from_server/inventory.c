/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
** the "inventory" command for server clients
*/
/**
 * @file inventory.c
 * @brief The file containing the handling of
 * the "inventory" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

static bool check_resource_args(
    char **args, size_t *ressource_id, size_t *quantity)
{
    *ressource_id = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS || *ressource_id >= RESOURCES_SIZE) {
        ERROR(my_create_str("Invalid resource ID: %s", args[2]));
        return false;
    }
    *quantity = my_get_number(args[3], DEFAULT_NB);
    if (my_errno != SUCCESS) {
        ERROR(my_create_str("Invalid quantity: %s", args[3]));
        return false;
    }
    return true;
}

static void update_inventory(
    server_t *server, player_t *player, size_t ressource_id, size_t quantity)
{
    player->inventory[ressource_id] += quantity;
    send_pin_to_gui(server, NULL, player);
    printf("Player #%zu's set %s x%zu\n",
        player->id, resources_names[ressource_id], quantity);
}

void handle_server_command_inventory(
    server_t *server, UNUSED client_t *client, char **args)
{
    size_t player_id = 0;
    size_t ressource_id = 0;
    size_t quantity = 0;

    DEBUG("Executing \"Inventory\" command");
    if (my_array_len((void **)args) != 4) {
        ERROR("Invalid number of arguments for \"Inventory\" command");
        return;
    }
    player_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || player_id == 0
    || player_id >= server->game.game_settings.next_player_id
    || get_player_by_id(&server->game, player_id) == NULL) {
        ERROR(my_create_str("Invalid player ID: %s", args[1]));
        return;
    }
    if (!check_resource_args(args, &ressource_id, &quantity))
        return;
    update_inventory(server, get_player_by_id(&server->game, player_id),
        ressource_id, quantity);
}
