/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_ht_dump function
*/
/**
 * @file my_ht_dump.c
 * @brief The file containing the my_ht_dump function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void display_entry_list(hashtable_entry_t *entry)
{
    if (entry == NULL)
        return;
    for (; entry != NULL; entry = entry->next)
        my_printf("> %d: %s\n", entry->key, entry->value);
}

/**
 * @brief Dumps (display) a hashtable
 * @param ht The hashtable to dump
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_ht_dump(hashtable_t *ht)
{
    if (ht == NULL)
        return;
    for (int i = 0; i < ht->len; i++) {
        my_printf("[%d]:\n", i);
        display_entry_list(ht->table[i]);
    }
}
