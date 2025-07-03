/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The test_ai.cpp
*/
/**
 * @file test_ai.cpp
 * @brief The test_ai.cpp
 * @author Nicolas TORO
 */

#include "tests.h"
#include "Player.hpp"

/* Example classic */
Test(create_player, test_create_player, .init = redirect_all_std)
{
    Player player("test");
}

Test(Player, team_name)
{
    Player player("team42");
    cr_assert_eq(player.getTeamName(), "team42", "Team name should be 'team42'");
}

Test(Player, alive_status)
{
    Player player("test");
    cr_assert(player.isAlive(), "Player should be alive by default");
    player.setAlive(false);
    cr_assert_not(player.isAlive(), "Player should not be alive after setAlive(false)");
}

Test(Player, command_queue)
{
    Player player("test");
    auto queue = std::make_shared<CommandsQueue>();
    player.setCommandsQueue(queue);
    queue->pushCommand("Forward");
    cr_assert(queue->hasCommands(), "Queue should have commands after push");
    std::string cmd = queue->popCommand();
    cr_assert_eq(cmd, "Forward", "Command popped should be 'Forward'");
    cr_assert_not(queue->hasCommands(), "Queue should be empty after pop");
}

Test(CommandsQueue, push_and_pop_multiple_commands)
{
    auto queue = std::make_shared<CommandsQueue>();
    queue->pushCommand("Left");
    queue->pushCommand("Right");
    queue->pushCommand("Forward");
    cr_assert(queue->hasCommands(), "Queue should have commands after multiple pushes");
    cr_assert_eq(queue->popCommand(), "Left", "First command should be 'Left'");
    cr_assert_eq(queue->popCommand(), "Right", "Second command should be 'Right'");
    cr_assert_eq(queue->popCommand(), "Forward", "Third command should be 'Forward'");
    cr_assert_not(queue->hasCommands(), "Queue should be empty after popping all commands");
}

Test(CommandsQueue, push_and_pop_response)
{
    auto queue = std::make_shared<CommandsQueue>();
    queue->pushResponse("ok");
    cr_assert(queue->hasResponses(), "Queue should have responses after push");
    cr_assert_eq(queue->popResponse(), "ok", "Response popped should be 'ok'");
    cr_assert_not(queue->hasResponses(), "Queue should be empty after popping response");
}

Test(Player, set_and_get_commands_queue)
{
    Player player("test");
    auto queue = std::make_shared<CommandsQueue>();
    player.setCommandsQueue(queue);
    cr_assert_eq(player.getCommandsQueue(), queue, "Player should return the same commands queue that was set");
}
