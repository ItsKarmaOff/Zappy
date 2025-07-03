/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The types used in the Zappy
*/
/**
 * @file ZappyTypes.hpp
 * @brief The types used in the Zappy
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef ZAPPYTYPES_HPP_
    #define ZAPPYTYPES_HPP_

    #include "Lib.hpp"

/**
 * @enum ResourceType
 * @brief Enumeration of all resource types in the Zappy game
 */
enum class ResourceType {
    FOOD,       ///< Food resource for survival
    LINEMATE,   ///< Linemate stone for evolution
    DERAUMERE,  ///< Deraumere stone for evolution
    SIBUR,      ///< Sibur stone for evolution
    MENDIANE,   ///< Mendiane stone for evolution
    PHIRAS,     ///< Phiras stone for evolution
    THYSTAME,   ///< Thystame stone for evolution
    UNKNOWN     ///< Unknown or invalid resource type
};

/**
 * @struct InventoryItem
 * @brief Represents an item in the player's inventory
 */
struct InventoryItem {
    ResourceType type; ///< The type of resource
    int quantity; ///< The quantity of this resource
    
    /**
     * @brief Constructor for InventoryItem
     * @param t The resource type
     * @param q The quantity
     */
    InventoryItem(ResourceType t, int q) : type(t), quantity(q) {}
};

/**
 * @brief Convert ResourceType to string representation
 * @param type The ResourceType to convert
 * @return String representation of the resource type
 */
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

/**
 * @brief Convert string to ResourceType
 * @param str The string to convert
 * @return The corresponding ResourceType
 */
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

#endif /* !ZAPPYTYPES_HPP_ */
