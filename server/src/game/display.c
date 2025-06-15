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
    printf(BOLD "%sTile (%zu, %zu):\n" RESET, tab, tile->position.x,
        tile->position.y);
    printf(BOLD "%s- Resources:" RESET "\n", tab);
    for (size_t index = 0; index < RESOURCES_SIZE; index++)
        printf(BOLD "%s    - %s:" RESET " %zu\n", tab, resources_names[index],
            tile->resources[index]);
}

void display_player(const player_t *player, char *tab)
{
    printf(BOLD "%sPlayer #%zu (%s):\n" RESET, tab, player->id,
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
    printf(BOLD "%s%s:\n" RESET, tab, team->name);
    printf(BOLD "%s- Players:" RESET " (%zu including %zu eggs)\n",
        tab, my_list_size(team->player_list), team->eggs_number);
    for (node_t *node = team->player_list; node != NULL; node = node->next)
        display_player(node->data, (tab == NULL ? "   " : "        "));
}

void display_game(const game_t *game)
{
    printf(BOLD UNDERLINE "Game Information:\n" RESET);
    printf(BOLD "- Map size:" RESET " %zu x %zu\n",
        game->game_settings.width, game->game_settings.height);
    printf(BOLD "- Frequency:" RESET " %zu\n",
        game->game_settings.frequency);
    printf(BOLD "- Show eggs: " RESET "%s\n" RESET,
        game->game_settings.show_eggs ? GREEN "true" : RED "false");
    printf(BOLD "- Auto end: " RESET "%s\n" RESET,
        game->game_settings.auto_end ? GREEN "true" : RED "false");
    printf(BOLD "- Winner team:" RESET " %s\n", game->winner_team_name ?
        game->winner_team_name : "None");
    printf(BOLD "- Teams:" RESET "(%zu)\n", game->game_settings.teams_number);
    for (size_t index = 1; index < game->game_settings.teams_number; index++)
        display_team(game->team_list[index], "    ");
    my_putchar('\n');
}
