/*
** EPITECH PROJECT, 2024
** zappy [WSL: Ubuntu]
** File description:
** ZappyTypes.hpp
*/

#pragma once

#include <string>

enum class ResourceType {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    UNKNOWN
};

struct InventoryItem {
    ResourceType type;
    int quantity;
    
    InventoryItem(ResourceType t, int q) : type(t), quantity(q) {}
};

inline std::string resourceTypeToString(ResourceType type) {
    switch (type) {
        case ResourceType::FOOD: return "food";
        case ResourceType::LINEMATE: return "linemate";
        case ResourceType::DERAUMERE: return "deraumere";
        case ResourceType::SIBUR: return "sibur";
        case ResourceType::MENDIANE: return "mendiane";
        case ResourceType::PHIRAS: return "phiras";
        case ResourceType::THYSTAME: return "thystame";
        default: return "unknown";
    }
}

inline ResourceType stringToResourceType(const std::string& str) {
    if (str == "food") return ResourceType::FOOD;
    if (str == "linemate") return ResourceType::LINEMATE;
    if (str == "deraumere") return ResourceType::DERAUMERE;
    if (str == "sibur") return ResourceType::SIBUR;
    if (str == "mendiane") return ResourceType::MENDIANE;
    if (str == "phiras") return ResourceType::PHIRAS;
    if (str == "thystame") return ResourceType::THYSTAME;
    return ResourceType::UNKNOWN;
}