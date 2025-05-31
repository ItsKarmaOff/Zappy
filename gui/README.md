# Zappy GUI

## Description

Zappy GUI is the graphical interface for the Zappy project, a multiplayer network game inspired by "The Hitchhiker's Guide to the Galaxy" universe. This interface allows real-time visualization of the evolution of the Trantor world where multiple teams compete to reach maximum elevation.

## Game Overview

In Zappy, players evolve on the planet Trantor, a toroidal world without relief where they must:
- Collect resources (food and 6 types of precious stones)
- Perform elevation rituals to level up
- Survive by managing their food
- Collaborate to reach the maximum level

The winning team is the first to have at least 6 players at the maximum level (level 8).

## Usage

```bash
./zappy_gui -p port -h machine
```

### Parameters
- `-p port`: Server port number
- `-h machine`: Server hostname

### Example
```bash
./zappy_gui -p 4242 -h localhost
```

## Features

TODO

## Communication Protocol

The GUI uses the TCP protocol to communicate with the Zappy server.

### Main Messages Received

| Command | Format | Description |
|---------|--------|-------------|
| `msz` | `msz X Y\n` | map size |
| `bct` | `bct X Y q0 q1 q2 q3 q4 q5 q6\n` | content of a tile |
| `mct` | `bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles` | content of the map (all the tiles) |
| `tna` | `tna N\n * nbr_teams` | name of all the teams |
| `pnw` | `pnw #n X Y O L N\n` | connection of a new player |
| `ppo` | `ppo #n X Y O\n` | player's position |
| `plv` | `plv #n L\n` | player's level |
| `pin` | `pin #n X Y q0 q1 q2 q3 q4 q5 q6\n` | player's inventory |
| `pex` | `pex #n\n` | expulsion |
| `pbc` | `pbc #n M\n` | broadcast |
| `pic` | `pic X Y L #n #n . . . \n` | start of an incantation (by the first player) |
| `pie` | `pie X Y R\n` | end of an incantation |
| `pfk` | `pfk #n\n` | egg laying by the player |
| `pdr` | `pdr #n i\n` | resource dropping |
| `pgt` | `pgt #n i\n` | resource collecting |
| `pdi` | `pdi #n\n` | death of a player |
| `enw` | `enw #e #n X Y\n` | an egg was laid by a player |
| `ebo` | `ebo #e\n` | player connection for an egg |
| `edi` | `edi #e\n` | death of an egg |
| `sgt` | `sgt T\n` | time unit request |
| `sst` | `sst T\n` | time unit modification |
| `seg` | `seg N\n` | end of game |
| `smg` | `smg M\n` | message from the server |
| `suc` | `suc\n` | unknown command |
| `sbp` | `sbp\n` | command parameter |

### Commands Sent to Server

| Command | Format | Description |
|---------|--------|-------------|
| `msz` | `msz\n` | map size |
| `bct` | `bct X Y\n` | content of a tile |
| `mct` | `mct\n` | content of the map (all the tiles) |
| `tna` | `tna\n` | name of all the teams |
| `ppo` | `ppo #n\n` | player's position |
| `plv` | `plv #n\n` | player's level |
| `pin` | `pin #n\n` | player's inventory |
| `sgt` | `sgt\n` | time unit request |
| `sst` | `sst T\n` | time unit modification |