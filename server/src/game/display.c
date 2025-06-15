/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The display.c
*/
/**
 * @file display.c
 * @brief The display.c
 * @author Nicolas TORO
 */

#include "game.h"

const char *orientation_names[] = {
    "None",
    "North",
    "East",
    "South",
    "West"
};

void display_tile(const tile_t *tile, char *tab)
{
    printf(BOLD "%sTile (%zu, %zu):" ENDL, tab, tile->position.x,
        tile->position.y);
    printf(BOLD "%s- Resources:" RESET "\n", tab);
    for (size_t index = 0; index < RESOURCES_SIZE; index++)
        printf(BOLD "%s    - %s:" RESET " %zu\n", tab, resources_names[index],
            tile->resources[index]);
}

void display_player(const player_t *player, char *tab)
{
    printf(BOLD "%sPlayer #%zu (%s):" ENDL, tab, player->id,
        player->is_egg ? "Egg" : "Player");
    printf(BOLD "%s- Position:" RESET " (%zu, %zu)\n",
        tab, player->position.x, player->position.y);
    printf(BOLD "%s- Orientation:" RESET " %s\n", tab,
        orientation_names[player->orientation]);
    printf(BOLD "%s- Level:" RESET " %zu\n", tab, player->level);
    printf(BOLD "%s- Inventory:" RESET "\n", tab);
    for (size_t index = 0; index < RESOURCES_SIZE; index++)
        printf(BOLD "%s    - %s:" RESET " %zu\n", tab, resources_names[index],
            player->inventory[index]);
}

void display_team(const team_t *team, char *tab)
{
    printf(BOLD "%s%s:" ENDL, tab, team->name);
    printf(BOLD "%s- Players:" RESET " (%zu including %zu eggs)\n",
        tab, my_list_size(team->player_list), team->eggs_number);
    for (node_t *node = team->player_list; node != NULL; node = node->next)
        display_player(node->data, (tab == NULL ? "   " : "        "));
}

static void display_game_settings(const game_settings_t *settings)
{
    printf(BOLD "- Map size:" RESET " %zu x %zu\n",
        settings->width, settings->height);
    printf(BOLD "- Frequency:" RESET " %zu\n", settings->frequency);
    printf(BOLD "- Game paused:" RESET " %s" ENDL,
        settings->is_paused ? GREEN "true" : RED "false");
    printf(BOLD "- Auto end:" RESET " %s" ENDL,
        settings->auto_end ? GREEN "true" : RED "false");
    printf(BOLD "- Show eggs:" RESET " %s" ENDL,
        settings->show_eggs ? GREEN "true" : RED "false");
    printf(BOLD "- No refill:" RESET " %s" ENDL,
        settings->no_refill ? GREEN "true" : RED "false");
    printf(BOLD "- Infinite food:" RESET " %s" ENDL,
        settings->infinite_food ? GREEN "true" : RED "false");
}

void display_game(const game_t *game)
{
    printf(BOLD UNDERLINE "Game Information:" ENDL);
    display_game_settings(&game->game_settings);
    printf(BOLD "- Winner team:" RESET " %s\n", game->winner_team_name ?
        game->winner_team_name : "None");
    printf(BOLD "- Teams:" RESET " (%zu)\n", game->game_settings.teams_number);
    for (size_t index = 1; index < game->game_settings.teams_number; index++)
        display_team(game->team_list[index], "    ");
    my_putchar('\n');
}
