/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_ht_search function
*/
/**
 * @file my_ht_search.c
 * @brief The file containing the my_ht_search function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static char *search_in_hashtable_entry(hashtable_entry_t *entry, ssize_t key)
{
    if (entry == NULL)
        return NULL;
    for (; entry != NULL; entry = entry->next) {
        if (entry->key == key)
            return entry->value;
    }
    return NULL;
}

/**
 * @brief Searches a key in a hashtable
 * @param ht The hashtable
 * @param key The key to search
 * @return <b>char*</b> The value of the key if found, NULL otherwise
 * @author Nicolas TORO
 */
char *my_ht_search(hashtable_t *ht, char *key)
{
    ssize_t hashed_key;
    size_t index;
    char *found_value = NULL;

    if (ht == NULL || key == NULL)
        return NULL;
    hashed_key = ht->hash(key, ht->len);
    index = hashed_key % ht->len;
    found_value = search_in_hashtable_entry(ht->table[index], hashed_key);
    if (found_value != NULL)
        return found_value;
    return NULL;
}
