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

Test(bct, test_bct_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4342", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_bct(server, &client, (char *[]){"bct", "0", "0", NULL});
}

Test(bct, test_bct_command_no_enough_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4343", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_bct(server, &client, (char *[]){"bct", NULL});
}

Test(bct, test_bct_command_bad_x, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4344", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_bct(server, &client, (char *[]){"bct", "20", "0", NULL});
}

Test(bct, test_bct_command_bad_y, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4345", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_bct(server, &client, (char *[]){"bct", "0", "20", NULL});
}

Test(mct, test_mct_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4346", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_mct(server, &client, (char *[]){"mct", NULL});
}

Test(mct, test_mct_command_too_many_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4347", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_mct(server, &client, (char *[]){"mct", "extra_arg", NULL});
}

Test(msz, test_msz_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4348", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_msz(server, &client, (char *[]){"msz", NULL});
}

Test(msz, test_msz_command_too_many_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4349", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_msz(server, &client, (char *[]){"msz", "extra_arg", NULL});
}

Test(pin, test_pin_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4350", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_pin(server, &client, (char *[]){"pin", "#1", NULL});
}

Test(pin, test_pin_command_invalid_player_id, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4351", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_pin(server, &client, (char *[]){"pin", "#-9999", NULL});
}

Test(pin, test_pin_command_no_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4352", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_pin(server, &client, (char *[]){"pin", NULL});
}

Test(pin, test_pin_command_invalid_format, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4353", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_pin(server, &client, (char *[]){"pin", "1", NULL});
}

Test(plv, test_plv_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4354", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_plv(server, &client, (char *[]){"plv", "#1", NULL});
}

Test(plv, test_plv_command_invalid_player_id, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4355", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_plv(server, &client, (char *[]){"plv", "#-9999", NULL});
}

Test(plv, test_plv_command_no_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4356", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_plv(server, &client, (char *[]){"plv", NULL});
}

Test(plv, test_plv_command_invalid_format, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4357", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_plv(server, &client, (char *[]){"plv", "1", NULL});
}

Test(ppo, test_ppo_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4358", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_ppo(server, &client, (char *[]){"ppo", "#1", NULL});
}

Test(ppo, test_ppo_command_invalid_player_id, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4359", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_ppo(server, &client, (char *[]){"ppo", "#-9999", NULL});
}

Test(ppo, test_ppo_command_no_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4360", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_ppo(server, &client, (char *[]){"ppo", NULL});
}

Test(ppo, test_ppo_command_invalid_format, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4361", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_ppo(server, &client, (char *[]){"ppo", "1", NULL});
}

Test(sgt, test_sgt_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4362", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_sgt(server, &client, (char *[]){"sgt", NULL});
}

Test(sgt, test_sgt_command_too_many_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4363", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_sgt(server, &client, (char *[]){"sgt", "extra_arg", NULL});
}

Test(sst, test_sst_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4364", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_sst(server, &client, (char *[]){"sst", "42", NULL});
}

Test(sst, test_sst_command_invalid_value, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4365", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_sst(server, &client, (char *[]){"sst", "invalid_value", NULL});
}

Test(sst, test_sst_command_no_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4366", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_sst(server, &client, (char *[]){"sst", NULL});
}

Test(tna, test_tna_command_valid, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4367", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_tna(server, &client, (char *[]){"tna", NULL});
}

Test(tna, test_tna_command_too_many_args, .init = redirect_all_std, .exit_code = 0)
{
    server_t *server = create_server(12, (char *[]){"zappy_server", "-p", "4368", "-x", "10", "-y", "10", "-n", "team" , "opps", "-c", "1"});
    client_t client = {
        .socket_fd = 0,
        .address = {0},
        .is_authenticated = true,
        .team_name = "GRAPHIC",
        .client_type = CLIENT_GUI,
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

    handle_gui_command_tna(server, &client, (char *[]){"tna", "extra_arg", NULL});
}