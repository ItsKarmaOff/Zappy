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

Test(server_all, test_server_all_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4442", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_all(server, &client, (char *[]){"all", NULL});
}

Test(server_all, test_server_all_too_many, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4443", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_all(server, &client, (char *[]){"all", "extra_arg", NULL});
}

Test(server_broadcast, test_server_broadcast_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4444", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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
        .client = &client
    };
    
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_server_command_broadcast(server, &client, (char *[]){"/broadcast", "0", "1", "message", NULL});
}

Test(server_broadcast, test_server_broadcast_not_enough_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4445", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_broadcast(server, &client, (char *[]){"/broadcast", NULL});
}

Test(server_broadcast, test_server_broadcast_invalid_x, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4446", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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
        .client = &client
    };
    
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_server_command_broadcast(server, &client, (char *[]){"/broadcast", "20", "0", "message", NULL});
}

Test(server_broadcast, test_server_broadcast_invalid_y, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4447", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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
        .client = &client
    };
    
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_server_command_broadcast(server, &client, (char *[]){"/broadcast", "0", "20", "message", NULL});
}

Test(server_broadcast, test_server_broadcast_same_tile, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4448", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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
        .client = &client
    };
    
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_server_command_broadcast(server, &client, (char *[]){"/broadcast", "0", "0", "message", NULL});
}

Test(server_clear, test_server_clear_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4449", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_clear(server, &client, (char *[]){"clear", NULL});
}

Test(server_clear, test_server_clear_not_enough_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4450", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_clear(server, &client, (char *[]){"clear", "extra_arg", NULL});
}

Test(server_client, test_server_client_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4451", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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
        .client = &client
    };
    
    my_push_back(&server->game.map[0][0].player_list, client2.player, UNKNOWN);

    handle_server_command_client(server, &client, (char *[]){"client", "1", NULL});
}

Test(server_client, test_server_client_not_enough_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4452", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "",
        .client_type = CLIENT_SERVER,
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

    handle_server_command_client(server, &client, (char *[]){"client", NULL});
}