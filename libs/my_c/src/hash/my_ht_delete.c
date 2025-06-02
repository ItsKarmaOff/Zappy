/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_ht_delete function
*/
/**
 * @file my_ht_delete.c
 * @brief The file containing the my_ht_delete function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void remove_hashtable_entry(hashtable_entry_t **begin,
    hashtable_entry_t *tmp)
{
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else
        *begin = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    FREE(tmp->value);
    FREE(tmp);
}

int search_delete_in_hashtable_entry(hashtable_entry_t **entry, ssize_t key)
{
    hashtable_entry_t *tmp = *entry;
    hashtable_entry_t *next = NULL;
    int result = 0;

    if (*entry == NULL)
        return 0;
    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->key == key) {
            remove_hashtable_entry(entry, tmp);
            result = 1;
        }
        tmp = next;
    }
    return result;
}

/**
 * @brief Deletes a key in a hashtable
 * @param ht The hashtable
 * @param key The key to delete
 * @return <b>bool</b> <u>false</u> if failure, <u>true</u> if success
 * @author Nicolas TORO
 */
bool my_ht_delete(hashtable_t *ht, char *key)
{
    bool result = false;
    ssize_t key_code;
    size_t index;

    if (ht == NULL || key == NULL)
        return result;
    key_code = ht->hash(key, ht->len);
    index = key_code % ht->len;
    if (search_delete_in_hashtable_entry(&ht->table[index], key_code))
        result = true;
    return result;
}
