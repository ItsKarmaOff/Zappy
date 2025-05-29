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

int search_delete_in_hashtable_entry(hashtable_entry_t **entry, int key)
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
 * @return <b>int</b> 0 if success, 84 if failure
 * @author Nicolas TORO
 */
int my_ht_delete(hashtable_t *ht, char *key)
{
    int result = 84;
    int key_code;
    int index;

    if (ht == NULL || key == NULL)
        return result;
    key_code = ht->hash(key, ht->len);
    index = key_code % ht->len;
    if (search_delete_in_hashtable_entry(&ht->table[index], key_code))
        result = 0;
    return result;
}
