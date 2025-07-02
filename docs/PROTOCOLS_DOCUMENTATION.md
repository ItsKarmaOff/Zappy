# Zappy Protocols Documentation

## Table of Contents

1. [AI Client/Server Protocol](#ai-clientserver-protocol)
2. [GUI Client/Server Protocol](#gui-clientserver-protocol)
3. [Server Internal Commands](#server-internal-commands)

---

## AI Client/Server Protocol

### Connection Process

1. Client opens socket to server
2. Communication sequence:
```
<-- WELCOME\n
--> TEAM-NAME\n
<-- CLIENT-NUM\n
<-- X Y\n
```

Where:
- `CLIENT-NUM`: Number of available slots for the team
- `X Y`: World dimensions


### Client Commands

| Command           | Syntax             | Time Limit | Response                                           | Description                 |
|-------------------|--------------------|------------|----------------------------------------------------|-----------------------------|
| **Movement**      |
| Forward           | `Forward\n`        | 7/f        | `ok\n` or `ko\n`                                   | Move up one tile            |
| Right             | `Right\n`          | 7/f        | `ok\n` or `ko\n`                                   | Turn 90° right              |
| Left              | `Left\n`           | 7/f        | `ok\n` or `ko\n`                                   | Turn 90° left               |
| **Information**   |
| Look              | `Look\n`           | 7/f        | `[tile1, tile2, ...]\n` or `ko\n`                  | Look around                 |
| Inventory         | `Inventory\n`      | 1/f        | `[linemate n, sibur n, ...]\n` or `ko\n`           | Show inventory              |
| Connect_nbr       | `Connect_nbr\n`    | -          | `value\n` or `ko\n`                                | Number of team unused slots |
| **Communication** |
| Broadcast         | `Broadcast text\n` | 7/f        | `ok\n` or `ko\n`                                   | Broadcast message           |
| **Actions**       |
| Take              | `Take object\n`    | 7/f        | `ok\n` or `ko\n`                                   | Take object                 |
| Set               | `Set object\n`     | 7/f        | `ok\n` or `ko\n`                                   | Set object down             |
| Fork              | `Fork\n`           | 42/f       | `ok\n` or `ko\n`                                   | Fork a player               |
| Eject             | `Eject\n`          | 7/f        | `ok\n` or `ko\n`                                   | Eject players from tile     |
| Incantation       | `Incantation\n`    | 300/f      | `Elevation underway\nCurrent level: k\n` or `ko\n` | Start incantation           |


### Server Notifications to Clients

| Notification      | Format                 | Description                           |
|-------------------|------------------------|---------------------------------------|
| Broadcast         | `message K, text\n`    | Message received (K = direction tile) |
| Ejection          | `eject: K\n`           | Player ejected (K = direction)        |
| Incantation start | `Elevation underway\n` | Incantation started                   |
| Incantation end   | `Current level: K\n`   | Incantation ended (K = new level)     |
| Death             | `dead\n`               | Player died                           |


### Resources and Objects

- **Food**: Keeps players alive (1 unit = 126 time units)
- **Stones**: linemate, deraumere, sibur, mendiane, phiras, thystame


### Elevation Requirements

| Level | Players | Linemate | Deraumere | Sibur | Mendiane | Phiras | Thystame |
|:-----:|:-------:|:--------:|:---------:|:-----:|:--------:|:------:|:--------:|
|  1→2  |    1    |    1     |     0     |   0   |    0     |   0    |    0     |
|  2→3  |    2    |    1     |     1     |   1   |    0     |   0    |    0     |
|  3→4  |    2    |    2     |     0     |   1   |    0     |   2    |    0     |
|  4→5  |    4    |    1     |     1     |   2   |    0     |   1    |    0     |
|  5→6  |    4    |    1     |     2     |   1   |    3     |   0    |    0     |
|  6→7  |    6    |    1     |     2     |   3   |    0     |   1    |    0     |
|  7→8  |    6    |    2     |     2     |   2   |    2     |   2    |    1     |

---

## GUI Client/Server Protocol

### Connection

GUI authenticates by sending `GRAPHIC` as team name.


### Protocol Symbols

| Symbol | Meaning                                                                            |
|--------|------------------------------------------------------------------------------------|
| X, Y   | Width/height or horizontal/vertical position                                       |
| q0-q6  | Resource quantities (food, linemate, deraumere, sibur, mendiane, phiras, thystame) |
| n      | Player number                                                                      |
| O      | Orientation: 1(N), 2(E), 3(S), 4(W)                                                |
| L      | Player or incantation level                                                        |
| e      | Egg number                                                                         |
| T      | Time unit                                                                          |
| N      | Team name                                                                          |
| R      | Incantation result                                                                 |
| M      | Message                                                                            |
| i      | Resource number                                                                    |


### Commands and Responses

#### Map Information
| Server → Client                              | Client → Server | Description          |
|----------------------------------------------|-----------------|----------------------|
| `msz X Y\n`                                  | `msz\n`         | Map size             |
| `bct X Y q0 q1 q2 q3 q4 q5 q6\n`             | `bct X Y\n`     | Content of a tile    |
| `bct X Y q0 q1 q2 q3 q4 q5 q6\n` * nbr_tiles | `mct\n`         | Content of all tiles |
| `tna N\n` * nbr_teams                        | `tna\n`         | Name of all teams    |

#### Player Actions
| Server → Client                     | Client → Server | Description           |
|-------------------------------------|-----------------|-----------------------|
| `pnw #n X Y O L N\n`                | -               | New player connection |
| `ppo #n X Y O\n`                    | `ppo #n\n`      | Player's position     |
| `plv #n L\n`                        | `plv #n\n`      | Player's level        |
| `pin #n X Y q0 q1 q2 q3 q4 q5 q6\n` | `pin #n\n`      | Player's inventory    |
| `pex #n\n`                          | -               | Player expulsion      |
| `pbc #n M\n`                        | -               | Player broadcast      |
| `pdr #n i\n`                        | -               | Resource dropping     |
| `pgt #n i\n`                        | -               | Resource collecting   |
| `pdi #n\n`                          | -               | Player death          |

#### Incantation
| Server → Client         | Description          |
|-------------------------|----------------------|
| `pic X Y L #n #n ...\n` | Start of incantation |
| `pie X Y R\n`           | End of incantation   |

#### Eggs
| Server → Client   | Description               |
|-------------------|---------------------------|
| `pfk #n\n`        | Egg laying by player      |
| `enw #e #n X Y\n` | Egg laid by player        |
| `ebo #e\n`        | Player connection for egg |
| `edi #e\n`        | Death of egg              |

#### Server Control
| Server → Client | Client → Server | Description            |
|-----------------|-----------------|------------------------|
| `sgt T\n`       | `sgt\n`         | Time unit request      |
| `sst T\n`       | `sst T\n`       | Time unit modification |
| `seg N\n`       | -               | End of game            |
| `smg M\n`       | -               | Server message         |
| `suc\n`         | -               | Unknown command        |
| `sbp\n`         | -               | Bad command parameter  |

---

## Server Internal Commands

### Information Commands

#### all
Display all server information including status, teams, and players.
```
Usage: /all
```

#### status
Display current server status.
```
Usage: /status
```


### Client Management

#### clients
Display list of all connected clients.
```
Usage: /clients
```

#### client
Display detailed information about a specific client.
```
Usage: /client <client_id>
Parameters:
  client_id: ID of the client to display
```

#### kick
Disconnect a client from the server.
```
Usage: /kick <client_id>
Parameters:
  client_id: ID of the client to kick
```


### Team Management

#### teams
Display list of all teams.
```
Usage: /teams
```

#### team
Display detailed information about a specific team.
```
Usage: /team <team_id>
Parameters:
  team_id: ID of the team to display
```

#### fork
Create a new egg for a team.
```
Usage: /fork <team_id>
Parameters:
  team_id: ID of the team
```


### Player Management

#### players
Display list of all players in the game.
```
Usage: /players
```

#### player
Display detailed information about a specific player.
```
Usage: /player
Parameters:
  player_id: ID of the player to display
```

#### level
Set the level of a player.
```
Usage: /level <player_id> <level>
Parameters:
  player_id: ID of the player
  level: New level (1-8)
```

#### inventory
Modify a player's inventory.
```
Usage: /inventory <player_id> <resource_id> <quantity>
Parameters:
  player_id: ID of the player
  resource_id: Resource type (0=food, 1=linemate, 2=deraumere, 3=sibur, 4=mendiane, 5=phiras, 6=thystame)
  quantity: New quantity
```

#### orientation
Set the orientation of a player.
```
Usage: /orientation <player_id> <orientation_id>
Parameters:
  player_id: ID of the player
  orientation_id: Orientation (1=North, 2=East, 3=South, 4=West)
```

#### tp
Teleport a player to a specific position.
```
Usage: /tp <player_id> <x> <y>
Parameters:
  player_id: ID of the player
  x: X coordinate
  y: Y coordinate
```


### World Management

#### map
Display the game map with resources.
```
Usage: /map
```

#### tile
Display information about a specific tile.
```
Usage: /tile <x> <y>
Parameters:
  x: X coordinate
  y: Y coordinate
```

#### frequency
Set the game frequency (time multiplier).
```
Usage: /frequency <frequency>
Parameters:
  frequency: New frequency value
```

### Communication Commands

#### broadcast
Broadcast a message to all clients from a specific position.
```
Usage: broadcast <x> <y> <message>
Parameters:
  x: X coordinate of broadcast origin
  y: Y coordinate of broadcast origin
  message: Message to broadcast
```

#### send_ai
Send a message to all AI clients.
```
Usage: /send_ai <message>
Parameters:
  message: Message to send
```

#### send_gui
Send a message to all GUI clients.
```
Usage: /send_gui <message>
Parameters:
  message: Message to send
```


### Debug and Control Commands

#### pause
Pause or resume the game.
```
Usage: /pause
```

#### debug_mode
Toggle debug mode on/off.
```
Usage: /debug_mode
```

#### extra_logs
Toggle extra logging on/off.
```
Usage: /extra_logs
```

#### infinite_food
Toggle infinite food mode on/off.
```
Usage: /infinite_food
```

#### no_refill
Toggle resource refill on/off.
```
Usage: /no_refill
```


### Utility Commands

#### help
Display help message with all available commands.
```
Usage: /help
```

#### clear
Clear the server console.
```
Usage: /clear
```

#### quit
Quit and stop the server.
```
Usage: /quit
```

---

## Notes

- All commands are case-sensitive
- Commands must end with `\n` (newline)
- Time calculations use formula: `action_time / frequency`
- Default frequency is 100
- Players start with 10 life units (1260 time units)
- World wraps around (spherical)
- Maximum 10 queued commands per client
- Server uses single-threaded poll() for socket multiplexing
