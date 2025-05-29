/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_delete_hashtable function
*/
/**
 * @file my_destroy_table.c
 * @brief The file containing the my_delete_hashtable function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void delete_hashtable_entry(hashtable_entry_t **begin)
{
    hashtable_entry_t *tmp = *begin;
    hashtable_entry_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        FREE(tmp->value);
        FREE(tmp);
        tmp = next;
    }
    *begin = NULL;
}

/**
 * @brief Deletes a hashtable
 * @param ht The hashtable to delete
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_hashtable(hashtable_t *ht)
{
    if (ht == NULL)
        return;
    for (int index = 0; index < ht->len; index++)
        delete_hashtable_entry(&ht->table[index]);
    FREE(ht->table);
    FREE(ht);
}
