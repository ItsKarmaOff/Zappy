/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_create_table function
*/
/**
 * @file my_create_table.c
 * @brief The file containing the my_create_table function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Creates a hashtable
 * @param hash The hash function to use
 * @param len The length of the hashtable
 * @return <b>hashtable_t*</b> The created hashtable
 * @author Nicolas TORO
 */
hashtable_t *my_create_hashtable(ssize_t (*hash)(char *, size_t), size_t len)
{
    hashtable_t *hashtable;

    if (hash == NULL || len < 1) {
        my_putstr_error("Error: invalid hashtable.\n");
        return NULL;
    }
    hashtable = my_calloc(1, sizeof(hashtable_t));
    hashtable->hash = hash;
    hashtable->len = len;
    hashtable->table = my_calloc(len, sizeof(hashtable_entry_t *));
    for (size_t i = 0; i < len; i++)
        hashtable->table[i] = NULL;
    return hashtable;
}
