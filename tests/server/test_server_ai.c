/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The server.c
*/
/**
 * @file server.c
 * @brief The server.c
 * @author Nicolas TORO
 */

#include "tests.h"
#include "server.h"

void close_server(void)
{
    my_exit(SUCCESS, GREEN "Server shutdown successfully." ENDL);
}

/* Example pour les fonctions qui exit */
Test(create_server1, test_create_server_with_no_args, .init = redirect_all_std, .exit_code = 84)
{
    create_server(1, (char *[]){"zappy_server"});
}

/* Example pour les fonctions classic */
Test(create_server2, test_create_server_with_good_args, .init = redirect_all_std, .fini = close_server, .exit_code = 0)
{
    create_server(12, (char *[]){"zappy_server", "-p", "4238", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1"});
}

Test(broadcast, test_broadcast_without_other_client, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4239", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    handle_ai_command_broadcast(server, &client, (char *[]){"broadcast", "Hello, world!", NULL});
}

Test(broadcast, test_broadcast_client_diff_till, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4240", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {1, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][1].player_list, client2.player, UNKNOWN);

    handle_ai_command_broadcast(server, &client, (char *[]){"broadcast", "Hello, world!", NULL});
}

Test(broadcast, test_broadcast_client_same_till, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4241", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_broadcast(server, &client, (char *[]){"broadcast", "Hello, world!", NULL});
}

Test(connect_nbr, test_connect_nbr_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_connect_nbr(server, &client, (char *[]){"connect_nbr", NULL});
}

Test(connect_nbr, test_connect_nbr_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4243", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_connect_nbr(server, &client, (char *[]){"connect_nbr", "failed", NULL});
}

Test(left, test_left_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4244", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_left(server, &client, (char *[]){"left", NULL});
}

Test(left, test_left_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4245", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_left(server, &client, (char *[]){"left", "failed", NULL});
}

Test(right, test_right_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4246", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_right(server, &client, (char *[]){"right", NULL});
}

Test(right, test_right_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4247", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_right(server, &client, (char *[]){"right", "failed", NULL});
}

Test(inventory, test_inventory_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4248", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_inventory(server, &client, (char *[]){"inventory", NULL});
}

Test(inventory, test_inventory_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4249", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_inventory(server, &client, (char *[]){"inventory", "failed", NULL});
}

Test(fork, test_fork_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4250", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_fork(server, &client, (char *[]){"fork", NULL});
}

Test(fork, test_fork_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4251", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_fork(server, &client, (char *[]){"fork", "failed", NULL});
}

Test(eject, test_eject_command_north, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4252", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_eject(server, &client, (char *[]){"eject", NULL});
}

Test(eject, test_eject_command_east, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4253", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = EAST,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_eject(server, &client, (char *[]){"eject", NULL});
}

Test(eject, test_eject_command_south, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4254", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = SOUTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_eject(server, &client, (char *[]){"eject", NULL});
}

Test(eject, test_eject_command_west, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4255", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = WEST,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_eject(server, &client, (char *[]){"eject", NULL});
}

Test(eject, test_eject_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4256", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_eject(server, &client, (char *[]){"eject", "failed", NULL});
}

Test(eject, test_eject_command_destroy_egg, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4257", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = true,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_eject(server, &client, (char *[]){"eject", NULL});
}

Test(forward, test_forward_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4258", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_forward(server, &client, (char *[]){"forward", NULL});
}

Test(forward, test_forward_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4259", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_forward(server, &client, (char *[]){"forward", "failed", NULL});
}

Test(look, test_look_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4260", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    server->game.game_settings.show_eggs = true;
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = true,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_ai_command_look(server, &client, (char *[]){"look", NULL});

    client.player->orientation = EAST;
    handle_ai_command_look(server, &client, (char *[]){"look", NULL});

    client.player->orientation = WEST;
    handle_ai_command_look(server, &client, (char *[]){"look", NULL});
}

Test(look, test_look_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4261", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_look(server, &client, (char *[]){"look", "failed", NULL});
}

Test(set, test_set_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4262", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    client.player->inventory[LINEMATE] = 1;

    handle_ai_command_set(server, &client, (char *[]){"set", "linemate", NULL});

    handle_ai_command_set(server, &client, (char *[]){"set", "linemate", NULL});
}

Test(set, test_set_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4263", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_set(server, &client, (char *[]){"set", "linemate", "failed", NULL});
}

Test(take, test_take_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4264", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    server->game.map[0][0].resources[LINEMATE] = 1;

    handle_ai_command_take(server, &client, (char *[]){"take", "linemate", NULL});

    handle_ai_command_take(server, &client, (char *[]){"take", "linemate", NULL});
}

Test(take, test_take_command_error, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4265", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    handle_ai_command_take(server, &client, (char *[]){"take", "linemate", "failed", NULL});
}

Test(incantation, test_incantation_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4266", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    server->current_clients_number = 1;
    server->client_list = my_calloc(2, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    server->game.map[0][0].resources[LINEMATE] = 1;

    handle_ai_command_incantation(server, &client, (char *[]){"incantation", NULL});

    client.next_action.cmd_function(server, &client, NULL);
}

Test(incantation, test_incantation_command_double_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4267", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    server->game.game_settings.show_eggs = true;
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };
    client_t client2 = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "team",
        .client_type = CLIENT_AI,
        .player = NULL,
        .command_queue = NULL,
        .next_action = {
            .action_args = NULL,
            .time_to_wait = 0.0,
            .cmd_function = NULL
        },
        .last_action_time = {0}
    };

    server->current_clients_number = 2;
    server->client_list = my_calloc(3, sizeof(client_t *));
    server->client_list[0] = &client;
    client.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client
    };
    server->client_list[1] = &client2;
    client2.player = &(player_t){
        .id = 1,
        .is_egg = false,
        .creator_id = 0,
        .position = {0, 0},
        .orientation = NORTH,
        .level = 1,
        .is_incanting = false,
        .last_eat_time = {0},
        .inventory = {0},
        .team = &(team_t){.name = "team", .eggs_number = 2},
        .client = &client2
    };

    my_push_back(&server->game.map[0][0].player_list, client.player, UNKNOWN);
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    server->game.map[0][0].resources[LINEMATE] = 1;

    handle_ai_command_incantation(server, &client, (char *[]){"incantation", NULL});

    client.next_action.cmd_function(server, &client, NULL);
}