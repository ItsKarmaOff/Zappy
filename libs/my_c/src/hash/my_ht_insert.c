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

static void push_front(hashtable_entry_t **begin, int key, char *value)
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
 * @return <b>int</b> 0 if success, 84 if failure
 * @author Nicolas TORO
 */
int my_ht_insert(hashtable_t *ht, char *key, char *value)
{
    int index;
    int hashed_key;

    if (ht == NULL || key == NULL || value == NULL)
        return my_putstr_error("Invalid insert arguments\n");
    hashed_key = ht->hash(key, ht->len);
    index = hashed_key % ht->len;
    for (hashtable_entry_t *tmp = ht->table[index];
    tmp != NULL; tmp = tmp->next) {
        if (tmp->key == hashed_key) {
            FREE(tmp->value);
            tmp->value = my_strdup(value);
            return 0;
        }
    }
    push_front(&ht->table[index], hashed_key, value);
    return 0;
}
