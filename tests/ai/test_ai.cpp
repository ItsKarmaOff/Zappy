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
#include <criterion/criterion.h>
#include <exception>
#include "Parser.hpp"
#include "Algo.hpp"

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

Test(CommandsQueue, empty_queue_pop_returns_empty_string)
{
    auto queue = std::make_shared<CommandsQueue>();
    cr_assert_eq(queue->popCommand(), "", "Popping from empty command queue should return empty string");
    cr_assert_eq(queue->popResponse(), "", "Popping from empty response queue should return empty string");
}

Test(CommandsQueue, interleaved_commands_and_responses)
{
    auto queue = std::make_shared<CommandsQueue>();
    queue->pushCommand("Forward");
    queue->pushResponse("ok");
    queue->pushCommand("Left");
    queue->pushResponse("ko");
    cr_assert(queue->hasCommands(), "Should have commands");
    cr_assert(queue->hasResponses(), "Should have responses");
    cr_assert_eq(queue->popCommand(), "Forward", "First command should be 'Forward'");
    cr_assert_eq(queue->popResponse(), "ok", "First response should be 'ok'");
    cr_assert_eq(queue->popCommand(), "Left", "Second command should be 'Left'");
    cr_assert_eq(queue->popResponse(), "ko", "Second response should be 'ko'");
    cr_assert_not(queue->hasCommands(), "Should have no commands left");
    cr_assert_not(queue->hasResponses(), "Should have no responses left");
}

Test(Player, alive_status_toggle)
{
    Player player("test");
    cr_assert(player.isAlive(), "Player should be alive by default");
    player.setAlive(false);
    cr_assert_not(player.isAlive(), "Player should not be alive after setAlive(false)");
    player.setAlive(true);
    cr_assert(player.isAlive(), "Player should be alive after setAlive(true)");
}

Test(CommandsQueue, stress_push_pop)
{
    auto queue = std::make_shared<CommandsQueue>();
    for (int i = 0; i < 1000; ++i)
        queue->pushCommand("cmd" + std::to_string(i));
    cr_assert(queue->hasCommands(), "Queue should have commands after many pushes");
    for (int i = 0; i < 1000; ++i)
        cr_assert_eq(queue->popCommand(), "cmd" + std::to_string(i), "Command order should be preserved");
    cr_assert_not(queue->hasCommands(), "Queue should be empty after popping all");
}

Test(Parser, parses_valid_arguments)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "4242", "-n", "team", "-h", "127.0.0.1"};

    try {
        parser = std::make_unique<Parser>(7, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Success &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
    cr_assert_eq(parser->getPort(), 4242, "Port should be 4242");
    cr_assert_eq(parser->getName(), "team", "Name should be 'team'");
    cr_assert_eq(parser->getHostname(), "127.0.0.1", "Machine should be '127.0.0.1'");
}

Test(Parser, throws_on_help)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "--help"};

    try {
        parser = std::make_unique<Parser>(2, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Success &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}

Test(Parser, throws_on_missing_arguments)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "4242", "-n", "team"};

    try {
        parser = std::make_unique<Parser>(5, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Critical &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}

Test(Parser, throws_on_invalid_port)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "0", "-n", "team", "-h", "localhost"};

    try {
        parser = std::make_unique<Parser>(7, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Critical &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}

Test(Parser, throws_on_empty_name)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "4242", "-n", "", "-h", "localhost"};

    try {
        parser = std::make_unique<Parser>(7, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Critical &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}

Test(Parser, throws_on_empty_machine)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "4242", "-n", "team", "-h", ""};

    try {
        parser = std::make_unique<Parser>(7, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Critical &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}

Test(Parser, throws_on_unknown_argument)
{
    std::unique_ptr<Parser> parser = nullptr;
    const char *argv[] = {"./zappy_ai", "-p", "4242", "-n", "team", "-x", "foo"};

    try {
        parser = std::make_unique<Parser>(7, const_cast<char **>(argv));
    } catch (const Lib::Exceptions::Critical &e) {
    } catch (...) {
        cr_assert_fail("Invalid exception thrown during parser construction");
    }
}
