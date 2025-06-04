/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_ht_insert function
*/
/**
 * @file my_ht_insert.c
 * @brief The file containing the my_ht_insert function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void push_front(hashtable_entry_t **begin, ssize_t key, char *value)
{
    hashtable_entry_t *new = my_calloc(1, sizeof(hashtable_entry_t));

    new->prev = NULL;
    new->value = my_strdup(value);
    new->key = key;
    new->next = *begin;
    if (*begin != NULL)
        (*begin)->prev = new;
    *begin = new;
}

/**
 * @brief Inserts a key-value pair in a hashtable
 * @param ht The hashtable
 * @param key The key to insert
 * @param value The value to insert
 * @return <b>bool</b> <u>false</u> if failure, <u>true</u> if success
 * @author Nicolas TORO
 */
bool my_ht_insert(hashtable_t *ht, char *key, char *value)
{
    size_t index;
    ssize_t hashed_key;

    if (ht == NULL || key == NULL || value == NULL)
        return false;
    hashed_key = ht->hash(key, ht->len);
    index = hashed_key % ht->len;
    for (hashtable_entry_t *tmp = ht->table[index];
    tmp != NULL; tmp = tmp->next) {
        if (tmp->key == hashed_key) {
            FREE(tmp->value);
            tmp->value = my_strdup(value);
            return true;
        }
    }
    push_front(&ht->table[index], hashed_key, value);
    return true;
}
