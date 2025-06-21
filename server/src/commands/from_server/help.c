/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The help.c
*/
/**
 * @file help.c
 * @brief The help.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

const command_help_t server_commands_help[] = {
    {"all", "\t\t\t\t\t",
        "Display all server information"},
    {"broadcast", "<x> <y> <message>\t\t",
        "Broadcast a message to all clients"},
    {"clear", "\t\t\t\t\t",
        "Clear the console"},
    {"client", "<client_id>\t\t\t",
        "Display information about a specific client"},
    {"clients", "\t\t\t\t",
        "Display the list of connected clients"},
    {"debug_mode", "\t\t\t\t",
        "Switch debug mode on or off"},
    {"extra_logs", "\t\t\t\t",
        "Switch extra logs on or off"},
    {"fork", "\t<team_id>\t\t\t",
        "Create a new egg for a team"},
    {"frequency", "<frequency>\t\t\t",
        "Set the game frequency"},
    {"help", "\t\t\t\t\t",
        "Display this help message"},
    {"infinite_food", "\t\t\t\t",
        "Switch infinite food mode on or off"},
    {"inventory", "<player_id> <resource_id> <quantity>",
        "Change the quantity of a resource in a player's inventory"},
    {"kick", "\t<client_id>\t\t\t",
        "Kick a client from the server"},
    {"level", "\t<player_id> <level>\t\t",
        "Set the level of a player"},
    {"map", "\t\t\t\t\t",
        "Display the game map"},
    {"no_refill", "\t\t\t\t",
        "Switch no refill mode on or off"},
    {"orientation", "<player_id> <orientation_id>\t",
        "Set the orientation of a player"},
    {"pause", "\t\t\t\t\t",
        "Pause or resume the game"},
    {"player", "<player_id>\t\t\t",
        "Display information about a specific player"},
    {"players", "\t\t\t\t",
        "Display the list of players"},
    {"quit", "\t\t\t\t\t",
        "Quit and stop the server"},
    {"send_ai", "<message>\t\t\t",
        "Send a message to all AI client"},
    {"send_gui", "<message>\t\t\t",
        "Send a message to all GUI client"},
    {"status", "\t\t\t\t",
        "Display the current server status"},
    {"team", "\t<team_id>\t\t\t",
        "Display information about a specific team"},
    {"teams", "\t\t\t\t\t",
        "Display the list of teams"},
    {"tile", "\t<x> <y>\t\t\t\t",
        "Display information about a specific tile"},
    {"tp", "\t<player_id> <x> <y>\t\t",
        "Teleport a player to a specific position"},
    {NULL, NULL, NULL}
};

void handle_server_command_help(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Help\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Help\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Available Commands:" ENDL);
    for (size_t i = 0; server_commands_help[i].command != NULL; i++)
        printf(BOLD "- %s" RESET "\t%s\t%s\n", server_commands_help[i].
            command, server_commands_help[i].args,
            server_commands_help[i].description);
    my_putstr(BOLD UNDERLINE "\nResource IDs:" ENDL);
    for (size_t index = 0; index < RESOURCES_SIZE; index++)
        printf(BOLD "- %zu:" RESET " %s\n", index, resources_names[index]);
    my_putstr(BOLD UNDERLINE "\nOrientations:" ENDL);
    for (size_t index = NORTH; index < WEST + 1; index++)
        printf(BOLD "- %zu:" RESET " %s\n", index, orientation_names[index]);
    my_putstr("========================================"
        "========================================\n");
}
