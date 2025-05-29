/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the hash functions
*/
/**
 * @file my_hash.c
 * @brief The file containing the hash functions
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief A simple hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>int</b> The hash value
 */
int my_hash_simple(char *key, int len)
{
    int hash = 0;

    for (int index = 0; key[index] != '\0'; index++)
        hash += key[index] * key[index];
    return hash;
}

/**
 * @brief A djb2 hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>int</b> The hash value
 */
int my_hash_djb2(char *key, int len)
{
    int hash = 5381;

    for (int index = 0; key[index] != '\0'; index++)
        hash = ((hash << 5) + hash) + key[index];
    return ABS(hash);
}

/**
 * @brief A p256 hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>int</b> The hash value
 */
int my_hash_p256(char *key, int len)
{
    int hash = 0;
    int multiplier = 1;

    for (int index = 0; key[index] != '\0'; index++) {
        hash += key[index] * multiplier;
        multiplier *= 256;
    }
    hash += multiplier * len;
    return ABS(hash);
}

/**
 * @brief A custom hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>int</b> The hash value
 */
int my_hash(char *key, int len)
{
    int hash_value = 0;

    for (int i = 0; key[i] != '\0'; i++)
        hash_value = hash_value ^ key[i] * 3907;
    return ABS(hash_value);
}
