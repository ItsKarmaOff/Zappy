/*
** EPITECH PROJECT, 2025
** Commands.cpp
** File description:
** Commands implementation
*/
/**
 * @file Commands.cpp
 * @brief Commands implementation for the GUI
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Commands.hpp"

namespace Gui
{
    //////////////////////// Constructors and Destructor ///////////////////////

    Commands::Commands(Graphics &graphical)
        : _graphical(graphical)
    {
        _commandHandlers = {
            {MSZ, [this](std::string &param) { handleMSZ(param); }},
            {BCT, [this](std::string &param) { handleBCT(param); }},
            {TNA, [this](std::string &param) { handleTNA(param); }},
            {PNW, [this](std::string &param) { handlePNW(param); }},
            {PPO, [this](std::string &param) { handlePPO(param); }},
            {PLV, [this](std::string &param) { handlePLV(param); }},
            {PIN, [this](std::string &param) { handlePIN(param); }},
            {PEX, [this](std::string &param) { handlePEX(param); }},
            {PBC, [this](std::string &param) { handlePBC(param); }},
            {PIC, [this](std::string &param) { handlePIC(param); }},
            {PIE, [this](std::string &param) { handlePIE(param); }},
            {PFK, [this](std::string &param) { handlePFK(param); }},
            {PDR, [this](std::string &param) { handlePDR(param); }},
            {PGT, [this](std::string &param) { handlePGT(param); }},
            {PDI, [this](std::string &param) { handlePDI(param); }},
            {ENW, [this](std::string &param) { handleENW(param); }},
            {EBO, [this](std::string &param) { handleEBO(param); }},
            {EDI, [this](std::string &param) { handleEDI(param); }},
            {SGT, [this](std::string &param) { handleSGT(param); }},
            {SST, [this](std::string &param) { handleSST(param); }},
            {SEG, [this](std::string &param) { handleSEG(param); }},
            {SMG, [this](std::string &param) { handleSMG(param); }},
            {SUC, [this](std::string &param) { handleSUC(param); }},
            {SBP, [this](std::string &param) { handleSBP(param); }}
        };
    }



    //////////////////////// Main Methods //////////////////////////////////////

    void Commands::handleResponses(std::shared_ptr<QueueManager> &queueManager)
    {
        while (queueManager->hasResponses()) {
            std::string response = queueManager->popResponse();
            size_t spacePos = response.find(' ');
            std::string command = (spacePos != std::string::npos) ? response.substr(0, spacePos) : response;
            std::string param = (spacePos != std::string::npos) ? response.substr(spacePos + 1) : "";

            if (_commandHandlers.contains(command)) {
                _commandHandlers[command](param);
            } else {
                ERROR << "Unknown command: " << command;
            }
        }
    }

    void Commands::handleMSZ(std::string &param)
    {
        DEBUG << "Handling MSZ command with param: " << param;

        std::istringstream iss(param);
        int width, height;

        if (!(iss >> width >> height))
            ERROR << "Invalid parameters for MSZ command: " << param;

        if (width <= 0 || height <= 0)
            ERROR << "Invalid dimensions for MSZ command: " << width << "x" << height;

        DEBUG_CONCAT << "Map size set to: " << width << "x" << height;

        _graphical.getGame()->getMapSize() = {static_cast<float>(width), static_cast<float>(height)};

        float rows = _graphical.getGame()->getMapSize().x;
        float cols = _graphical.getGame()->getMapSize().y;

        // creating tiles if needed
        if (_graphical.getGame()->getTiles().size() <= rows * cols) {
            // _graphical.getGame()->getTiles().clear();
            for (float i = 0; i < rows; i++) {
                for (float j = 0; j < cols; j++) {
                    if (_graphical.getGame()->getTiles().contains({i, j}))
                        continue;
                    _graphical.getGame()->getTiles()[{i, j}] = TileInfo({i * TILE_SIZE, 0, j * TILE_SIZE});
                }
            }
        } else if (_graphical.getGame()->getTiles().size() >= rows * cols) {
            for (auto &[k, v] : _graphical.getGame()->getTiles()) {
                if (k.x >= rows || k.y >= cols)
                    _graphical.getGame()->getTiles().erase(k);
            }
        }
    }

    void Commands::handleBCT(std::string &param)
    {
        DEBUG << "Handling BCT command with param: " << param;

        std::istringstream iss(param);
        int width, height;
        int food, linemate, deraumere, sibur, mendiane, phiras, thystame;

        if (!(iss >> width >> height >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame))
            ERROR << "Invalid parameters for BCT command: " << param;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for BCT command: " << width << "x" << height;

        if (food < 0 || linemate < 0 || deraumere < 0 || sibur < 0 || mendiane < 0 || phiras < 0 || thystame < 0)
            ERROR << "Invalid quantities for BCT command: " << food << ", " << linemate << ", " << deraumere << ", "
                << sibur << ", " << mendiane << ", " << phiras << ", " << thystame;

        DEBUG_CONCAT << "Tile at (" << width << ", " << height << ") has resources: "
        << food << " food, "
        << linemate << " linemate, "
        << deraumere << " deraumere, "
        << sibur << " sibur, "
        << mendiane << " mendiane, "
        << phiras << " phiras, "
        << thystame << " thystame";

        // assigning resources to the tile
        if (_graphical.getGame()->getTiles().contains({static_cast<float>(width), static_cast<float>(height)})) {
            std::map<std::string, int> &content = _graphical.getGame()->getTiles().at({static_cast<float>(width), static_cast<float>(height)}).getContent();
            content["food"] = food;
            content["linemate"] = linemate;
            content["deraumere"] = deraumere;
            content["sibur"] = sibur;
            content["mendiane"] = mendiane;
            content["phiras"] = phiras;
            content["thystame"] = thystame;
        }
    }

    void Commands::handleTNA(std::string &param)
    {
        DEBUG << "Handling TNA command with param: " << param;

        std::istringstream iss(param);
        std::string teamName;

        if (!(iss >> teamName))
            ERROR << "Invalid parameters for TNA command: " << param;

        if (teamName.empty())
            ERROR << "Team name cannot be empty for TNA command";

        DEBUG_CONCAT << "Team name set to: " << teamName;

        static Color teamColors[] = {
            RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, PINK, LIME,
            SKYBLUE, VIOLET, BROWN, DARKGREEN, MAGENTA, GOLD
        };

        if (!_graphical.getGame()->getTeams().contains(teamName)) {
            _graphical.getGame()->getTeams()[teamName] = TeamInfo();
            int randomIndex = GetRandomValue(0, sizeof(teamColors) / sizeof(Color) - 1);
            _graphical.getGame()->getTeams()[teamName].setColor(teamColors[randomIndex]);
        }
    }

    void Commands::handlePNW(std::string &param)
    {
        DEBUG << "Handling PNW command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int width, height;
        int orientation;
        int level;
        std::string teamName;

        if (!(iss >> player >> width >> height >> orientation >> level >> teamName))
            ERROR << "Invalid parameters for PNW command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PNW command: " << player;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for PNW command: " << width << "x" << height;

        if (orientation < 1 || orientation > 4)
            ERROR << "Invalid orientation for PNW command: " << orientation;

        if (level < 1 || level > 8)
            ERROR << "Invalid level for PNW command: " << level;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " joined at (" << width << ", " << height << ") with orientation "
            << orientation << " and level " << level << " in team " << teamName;
        if (!_graphical.getGame()->getTeams().contains(teamName)) {
            ERROR << "Team: [" << teamName << "] doesn't exist";
            return;
        }
        TeamInfo &team = _graphical.getGame()->getTeams()[teamName];
        if (!team.getPlayers().contains(playerId)) {
            team.getPlayers()[playerId] = std::make_shared<PlayerInfo>(teamName);
            _graphical.getGame()->getPlayers()[playerId] = team.getPlayers()[playerId];
        }
        std::shared_ptr<PlayerInfo> &playerI = team.getPlayers()[playerId];
        playerI->setLevel(level);
        playerI->setOrientation(orientation);
        playerI->setPos({static_cast<float>(width), static_cast<float>(height)});
        playerI->setColor(team.getColor());
    }

    void Commands::handlePPO(std::string &param)
    {
        DEBUG << "Handling PPO command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int width, height;
        int orientation;

        if (!(iss >> player >> width >> height >> orientation))
            ERROR << "Invalid parameters for PPO command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PPO command: " << player;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for PPO command: " << width << "x" << height;

        if (orientation < 1 || orientation > 4)
            ERROR << "Invalid orientation for PPO command: " << orientation;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " position updated to (" << width << ", " << height
            << ") with orientation " << orientation;

        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }
        if (_graphical.getGame()->getPlayers()[playerId]->getPos() != Vector2{static_cast<float>(width), static_cast<float>(height)})
            _graphical.getGame()->getPlayers()[playerId]->setPos({static_cast<float>(width), static_cast<float>(height)});
        if (_graphical.getGame()->getPlayers()[playerId]->getOrientation() != static_cast<size_t>(orientation))
            _graphical.getGame()->getPlayers()[playerId]->setOrientation(static_cast<size_t>(orientation));
    }

    void Commands::handlePLV(std::string &param)
    {
        DEBUG << "Handling PLV command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int level;

        if (!(iss >> player >> level))
            ERROR << "Invalid parameters for PLV command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PLV command: " << player;

        if (level < 1 || level > 8)
            ERROR << "Invalid level for PLV command: " << level;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " level set to: " << level;

        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }
        if (_graphical.getGame()->getPlayers()[playerId]->getLevel() != static_cast<size_t>(level))
            _graphical.getGame()->getPlayers()[playerId]->setLevel(static_cast<size_t>(level));
    }

    void Commands::handlePIN(std::string &param)
    {
        DEBUG << "Handling PIN command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int width, height;
        int food, linemate, deraumere, sibur, mendiane, phiras, thystame;

        if (!(iss >> player >> width >> height >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame))
            ERROR << "Invalid parameters for PIN command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PIN command: " << player;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for PIN command: " << width << "x" << height;

        if (food < 0 || linemate < 0 || deraumere < 0 || sibur < 0 || mendiane < 0 || phiras < 0 || thystame < 0)
            ERROR << "Invalid quantities for PIN command: " << food << ", " << linemate << ", " << deraumere << ", "
                << sibur << ", " << mendiane << ", " << phiras << ", " << thystame;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " inventory at (" << width << ", " << height << ") has resources: "
            << food << " food, " << linemate << " linemate, " << deraumere << " deraumere, " << sibur << " sibur, "
            << mendiane << " mendiane, " << phiras << " phiras, " << thystame << " thystame";

        std::map<PlayerInfo::ResourceType, size_t> newInventory = {
            {PlayerInfo::ResourceType::FOOD, static_cast<size_t>(food)},
            {PlayerInfo::ResourceType::LINEMATE, static_cast<size_t>(linemate)},
            {PlayerInfo::ResourceType::DERAUMERE, static_cast<size_t>(deraumere)},
            {PlayerInfo::ResourceType::SIBUR, static_cast<size_t>(sibur)},
            {PlayerInfo::ResourceType::MENDIANE, static_cast<size_t>(mendiane)},
            {PlayerInfo::ResourceType::PHIRAS, static_cast<size_t>(phiras)},
            {PlayerInfo::ResourceType::THYSTAME, static_cast<size_t>(thystame)}
        };

        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }

        if (_graphical.getGame()->getPlayers()[playerId]->getPos() != Vector2{static_cast<float>(width), static_cast<float>(height)})
            _graphical.getGame()->getPlayers()[playerId]->setPos({static_cast<float>(width), static_cast<float>(height)});
        _graphical.getGame()->getPlayers()[playerId]->setInventory(newInventory);
    }

    void Commands::handlePEX(std::string &param)
    {
        DEBUG << "Handling PEX command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;

        if (!(iss >> player))
            ERROR << "Invalid parameters for PEX command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PEX command: " << player;

        playerId = std::stoi(player.substr(1));
        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }
        for (auto &[k, team] : _graphical.getGame()->getTeams()) {
            // return 0 si ça n'a pas trouvé, donc on peut le faire pour chaque team sans conséquence
            team.getPlayers().erase(playerId);
        }
        _graphical.getGame()->getPlayers().erase(playerId);
        DEBUG_CONCAT << "Player #" << playerId << " has been expelled";

    }

    void Commands::handlePBC(std::string &param)
    {
        DEBUG << "Handling PBC command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        std::string message;

        if (!(iss >> player))
            ERROR << "Invalid parameters for PBC command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PBC command: " << player;

        playerId = std::stoi(player.substr(1));

        std::getline(iss, message);

        if (message.empty())
            ERROR << "Message cannot be empty for PBC command";

        if (message[0] == ' ')
            message = message.substr(1);
        if (playerId != -1 && !_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << " doesn't exist.";
            return;
        }
        _graphical.getChatbox()->addMessage(
            message,
            (playerId != -1) ? "Player#" + std::to_string(playerId) : "Server Broadcast",
            (playerId != -1) ? _graphical.getGame()->getPlayers().at(playerId)->getColor() : WHITE
        );
        DEBUG_CONCAT << "Player #" << playerId << " broadcasts: " << message;
    }

    void Commands::handlePIC(std::string &param)
    {
        DEBUG << "Handling PIC command with param: " << param;

        std::istringstream iss(param);
        std::string players;
        std::vector<int> playerIds;
        int width, height;
        int level;

        if (!(iss >> width >> height >> level))
            ERROR << "Invalid parameters for PIC command: " << param;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for PIC command: " << width << "x" << height;

        if (level < 1 || level > 8)
            ERROR << "Invalid level for PIC command: " << level;

        while (iss >> players) {
            if (players.empty() || players[0] != '#' || players.size() < 2)
                ERROR << "Invalid player format in PIC command: " << players;
            playerIds.push_back(std::stoi(players.substr(1)));
        }

        if (playerIds.empty())
            ERROR << "No valid players found in PIC command";

        DEBUG_CONCAT << "Incantation started at (" << width << ", " << height << ") level " << level << " with "
            << playerIds.size() << " players";
        for (int playerId : playerIds) {
            if (!_graphical.getGame()->getPlayers().contains(playerId)) {
                ERROR << "Player " << playerId << "doesn't exist.";
                continue;
            }
            std::shared_ptr<PlayerInfo> &playerInfo = _graphical.getGame()->getPlayers()[playerId];
            playerInfo->setIncanting(true);
        }
    }

    void Commands::handlePIE(std::string &param)
    {
        DEBUG << "Handling PIE command with param: " << param;

        std::istringstream iss(param);
        int width, height;
        int incantationResult;

        if (!(iss >> width >> height >> incantationResult))
            ERROR << "Invalid parameters for PIE command: " << param;

        if (width < 0 || height < 0 || incantationResult < 0)
            ERROR << "Invalid parameters for PIE command: " << width << "x" << height << ", result: " << incantationResult;

        DEBUG_CONCAT << "Incantation at (" << width << ", " << height << ") "
            << (incantationResult ? "succeeded" : "failed");
        for (auto &[id, player] : _graphical.getGame()->getPlayers()) {
            if (player->getPos() == Vector2{static_cast<float>(width), static_cast<float>(height)}) {
                player->setIncanting(false);
                _graphical.getQueueManager()->pushCommand({"plv", ("#" + std::to_string(id))});
            }
        }
    }

    void Commands::handlePFK(std::string &param)
    {
        DEBUG << "Handling PFK command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;

        if (!(iss >> player))
            ERROR << "Invalid parameters for PFK command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PFK command: " << player;

        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Player #" << playerId << " has laid an egg";
    }

    void Commands::handlePDR(std::string &param)
    {
        DEBUG << "Handling PDR command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int resourceNumber;

        if (!(iss >> player >> resourceNumber))
            ERROR << "Invalid parameters for PDR command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PDR command: " << player;

        if (resourceNumber < 0 || resourceNumber > 6)
            ERROR << "Invalid resource number for PDR command: " << resourceNumber;

        playerId = std::stoi(player.substr(1));
        std::shared_ptr<PlayerInfo> playerInfo = _graphical.getGame()->getPlayers()[playerId];

        DEBUG_CONCAT << "Player #" << playerId << " dropped resource number " << resourceNumber;

        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }
        _graphical.getGame()->getPlayers()[playerId]->removeResource(static_cast<PlayerInfo::ResourceType>(resourceNumber), 1);
        _graphical.getQueueManager()->pushCommand({"bct",
            std::to_string(static_cast<int>(playerInfo->getPos().x)),
            std::to_string(static_cast<int>(playerInfo->getPos().y))});

    }

    void Commands::handlePGT(std::string &param)
    {
        DEBUG << "Handling PGT command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        int resourceNumber;

        if (!(iss >> player >> resourceNumber))
            ERROR << "Invalid parameters for PGT command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PGT command: " << player;

        if (resourceNumber < 0 || resourceNumber > 6)
            ERROR << "Invalid resource number for PGT command: " << resourceNumber;

        playerId = std::stoi(player.substr(1));
        std::shared_ptr<PlayerInfo> playerInfo = _graphical.getGame()->getPlayers()[playerId];

        DEBUG_CONCAT << "Player #" << playerId << " got resource number " << resourceNumber;

        playerInfo->addResource(static_cast<PlayerInfo::ResourceType>(resourceNumber), 1);
        _graphical.getQueueManager()->pushCommand({"bct",
            std::to_string(static_cast<int>(playerInfo->getPos().x)),
            std::to_string(static_cast<int>(playerInfo->getPos().y))});
        PlaySound(SoundsManager::getInstance().getSounds()[SoundsManager::PICKUP_SOUND]);
    }

    void Commands::handlePDI(std::string &param)
    {
        DEBUG << "Handling PDI command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;

        if (!(iss >> player))
            ERROR << "Invalid parameters for PDI command: " << param;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for PDI command: " << player;

        playerId = std::stoi(player.substr(1));
        if (!_graphical.getGame()->getPlayers().contains(playerId)) {
            ERROR << "Player " << playerId << "doesn't exist.";
            return;
        }
        for (auto &[k, team] : _graphical.getGame()->getTeams()) {
            // return 0 si ça n'a pas trouvé, donc on peut le faire pour chaque team sans conséquence
            team.getPlayers().erase(playerId);
        }
        _graphical.getGame()->getPlayers().erase(playerId);
        DEBUG_CONCAT << "Player #" << playerId << " has been expelled";

        DEBUG_CONCAT << "Player #" << playerId << " has died";
    }

    void Commands::handleENW(std::string &param)
    {
        DEBUG << "Handling ENW command with param: " << param;

        std::istringstream iss(param);
        std::string player;
        int playerId;
        std::string eggNumber;
        int eggId;
        int width, height;

        if (!(iss >> eggNumber >> player >> width >> height))
            ERROR << "Invalid parameters for ENW command: " << param;

        if (eggNumber.empty() || eggNumber[0] != '#' || eggNumber.size() < 2)
            ERROR << "Invalid egg number format for ENW command: " << eggNumber;

        if (player.empty() || player[0] != '#' || player.size() < 2)
            ERROR << "Invalid player format for ENW command: " << player;

        if (width < 0 || height < 0)
            ERROR << "Invalid coordinates for ENW command: " << width << "x" << height;

        eggId = std::stoi(eggNumber.substr(1));
        playerId = std::stoi(player.substr(1));

        DEBUG_CONCAT << "Egg #" << eggId << " laid by Player #" << playerId
            << " at (" << width << ", " << height << ")";

        TeamInfo &team = _graphical.getGame()->getTeams()["UnknownTeam"];
        if (!team.getPlayers().contains(eggId)) {
            team.getPlayers()[eggId] = std::make_shared<PlayerInfo>("UnknownTeam");
            _graphical.getGame()->getPlayers()[eggId] = team.getPlayers()[eggId];
        }

        std::shared_ptr<PlayerInfo> &eggI = team.getPlayers()[eggId];
        eggI->setLevel(0);
        eggI->setPos({static_cast<float>(width), static_cast<float>(height)});
        eggI->setColor(WHITE);
    }

    void Commands::handleEBO(std::string &param)
    {
        DEBUG << "Handling EBO command with param: " << param;

        std::istringstream iss(param);
        std::string eggNumber;
        int eggId;

        if (!(iss >> eggNumber))
            ERROR << "Invalid parameters for EBO command: " << param;

        if (eggNumber.empty() || eggNumber[0] != '#' || eggNumber.size() < 2)
            ERROR << "Invalid egg number format for EBO command: " << eggNumber;

        eggId = std::stoi(eggNumber.substr(1));

        DEBUG_CONCAT << "Player connected from egg #" << eggId;
    }

    void Commands::handleEDI(std::string &param)
    {
        DEBUG << "Handling EDI command with param: " << param;

        std::istringstream iss(param);
        std::string eggNumber;
        int eggId;

        if (!(iss >> eggNumber))
            ERROR << "Invalid parameters for EDI command: " << param;

        if (eggNumber.empty() || eggNumber[0] != '#' || eggNumber.size() < 2)
            ERROR << "Invalid egg number format for EDI command: " << eggNumber;

        eggId = std::stoi(eggNumber.substr(1));

        DEBUG_CONCAT << "Egg #" << eggId << " has been destroyed";

        if (!_graphical.getGame()->getPlayers().contains(eggId))
            ERROR << "Egg #" << eggId << " not found in players list";

        _graphical.getGame()->getPlayers().erase(eggId);
    }

    void Commands::handleSGT(std::string &param)
    {
        DEBUG << "Handling SGT command with param: " << param;

        std::istringstream iss(param);
        int time;

        if (!(iss >> time))
            ERROR << "Invalid parameters for SGT command: " << param;

        if (time < 0)
            ERROR << "Invalid time for SGT command: " << time;

        if (!_graphical.getPause())
            _graphical.setPause(std::make_shared<PauseInfo>());
        _graphical.getPause()->setTimeUnit(time);

        DEBUG_CONCAT << "Server time unit retrieved: " << time;
    }

    void Commands::handleSST(std::string &param)
    {
        DEBUG << "Handling SST command with param: " << param;

        std::istringstream iss(param);
        int time;

        if (!(iss >> time))
            ERROR << "Invalid parameters for SST command: " << param;

        if (time <= 0)
            ERROR << "Invalid time for SST command: " << time;

        if (!_graphical.getPause())
            _graphical.setPause(std::make_shared<PauseInfo>());
        _graphical.getPause()->setTimeUnit(time);
        DEBUG_CONCAT << "Server time unit modified to: " << time;
    }

    void Commands::handleSEG(std::string &param)
    {
        DEBUG << "Handling SEG command with param: " << param;

        std::istringstream iss(param);
        std::string teamName;

        if (!(iss >> teamName))
            ERROR << "Invalid parameters for SEG command: " << param;

        if (teamName.empty())
            ERROR << "Team name cannot be empty for SEG command";

        if (!_graphical.getGame()->getTeams().contains(teamName)) {
            ERROR << "Team: [" << teamName << "] doesn't exist";
            return;
        }
        DEBUG_CONCAT << "Game ended - Team " << teamName << " has won!";
        if (!_graphical.getEndInfo())
            _graphical.getEndInfo() = (std::make_shared<EndInfo>());
        _graphical.getEndInfo()->winner = teamName + " has won!";
        _graphical.getEndInfo()->teamColor = _graphical.getGame()->getTeams()[teamName].getColor();
        _graphical.getScene() = Graphics::END;
    }

    void Commands::handleSMG(std::string &param)
    {
        DEBUG << "Handling SMG command with param: " << param;

        std::istringstream iss(param);
        std::string message = param;

        if (message.empty())
            ERROR << "Message cannot be empty for SMG command";

        DEBUG_CONCAT << "Server message: " << message;
        _graphical.getChatbox()->addMessage(
            message,
            "Server",
            WHITE
        );
    }

    void Commands::handleSUC(std::string &param)
    {
        DEBUG << "Handling SUC command with param: " << param;

        if (!param.empty())
            ERROR << "Invalid parameters for SUC command: " << param;

        DEBUG_CONCAT << "unknown command";
    }

    void Commands::handleSBP(std::string &param)
    {
        DEBUG << "Handling SBP command with param: " << param;

        std::string message = param;

        if (message.empty())
            DEBUG_CONCAT << "Command parameter error (no details provided)";
        else
            DEBUG_CONCAT << "Command parameter error: " << message;

        ERROR << "Server reports command parameter error" << (param.empty() ? "" : ": " + param);
    }
}
