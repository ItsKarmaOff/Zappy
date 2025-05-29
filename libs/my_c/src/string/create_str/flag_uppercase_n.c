/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_uppercase_n function
*/
/**
 * @file flag_uppercase_n.c
 * @brief The file containing the flag_uppercase_n function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *get_node_int(node_t *node)
{
    if (node->type == SIGNED_CHAR)
        return my_create_str("%hhd", *((char *)node->data));
    if (node->type == SHORT)
        return my_create_str("%hd", *((short *)node->data));
    if (node->type == INT)
        return my_create_str("%d", *((int *)node->data));
    if (node->type == LONG)
        return my_create_str("%ld", *((long *)node->data));
    if (node->type == LONG_LONG)
        return my_create_str("%lld", *((long long *)node->data));
    return NULL;
}

static char *get_node_uint(node_t *node)
{
    if (node->type == UNSIGNED_CHAR)
        return my_create_str("%hhu", *((unsigned char *)node->data));
    if (node->type == UNSIGNED_SHORT)
        return my_create_str("%hu", *((unsigned short *)node->data));
    if (node->type == UNSIGNED_INT)
        return my_create_str("%u", *((unsigned int *)node->data));
    if (node->type == UNSIGNED_LONG)
        return my_create_str("%lu", *((unsigned long *)node->data));
    if (node->type == UNSIGNED_LONG_LONG)
        return my_create_str("%llu", *((unsigned long long *)node->data));
    if (node->type == SIZE_T)
        return my_create_str("%zu", *((size_t *)node->data));
    return NULL;
}

static char *get_node_decimal(node_t *node)
{
    if (node->type == FLOAT)
        return my_create_str("%f", *((float *)node->data));
    if (node->type == DOUBLE)
        return my_create_str("%f", *((double *)node->data));
    if (node->type == LONG_DOUBLE)
        return my_create_str("%Lf", *((long double *)node->data));
    return NULL;
}

static char *get_node_data(node_t *node)
{
    if (node->data == NULL)
        return NULL;
    if (node->type >= SIGNED_CHAR && node->type <= LONG_LONG)
        return get_node_int(node);
    if (node->type >= UNSIGNED_CHAR && node->type <= UNSIGNED_LONG_LONG)
        return get_node_uint(node);
    if (node->type >= FLOAT && node->type <= LONG_DOUBLE)
        return get_node_decimal(node);
    if (node->type == CHAR)
        return my_create_str("%c", *((char *)node->data));
    if (node->type == STRING)
        return my_create_str("%s", ((char *)node->data));
    if (node->type == ARRAY_OF_STRING)
        return my_create_str("%S", ((char **)node->data));
    if (node->type == VOID)
        return my_create_str("%p", node->data);
    return NULL;
}

static intmax_t node_to_str_node(node_t *list, node_t **new_list)
{
    intmax_t list_len = my_list_size_circled(list);
    intmax_t total_len = 0;
    char *tmp_str = NULL;

    for (intmax_t index = 0; index < list_len; index++) {
        tmp_str = get_node_data(list);
        total_len += my_strlen(tmp_str);
        my_push_back(new_list, tmp_str, STRING);
        list = list->next;
        if (index != list_len - 1) {
            my_push_back(new_list, my_strdup(" ---> "), STRING);
            total_len += 6;
        }
    }
    return total_len;
}

static char *get_text(format_t *str_struct)
{
    node_t *list = va_arg(str_struct->format_list, node_t *);
    node_t *tmp = NULL;
    intmax_t total_len = node_to_str_node(list, &tmp);
    char *tmp_result = NULL;
    char *result = NULL;

    tmp_result = my_calloc(total_len + 1, sizeof(char));
    for (node_t *new_tmp = tmp; new_tmp != NULL; new_tmp = new_tmp->next)
        my_strcat(tmp_result, new_tmp->data);
    my_delete_list(&tmp);
    if (str_struct->current_flag.precision) {
        result = my_strndup(tmp_result,
            str_struct->current_flag.precision_value);
        FREE(tmp_result);
    } else
        result = tmp_result;
    return result;
}

static void add_text(format_t *str_struct, char **str_list)
{
    if (!str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[1], STRING);
    my_push_back(&str_struct->str_list, str_list[0], STRING);
    if (str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[1], STRING);
}

void flag_uppercase_n(format_t *str_struct)
{
    char *str_list[] = {NULL, NULL};

    str_list[0] = get_text(str_struct);
    str_struct->total_len += my_strlen(str_list[0]);
    str_struct->current_flag.width -= my_strlen(str_list[0]);
    if (str_struct->current_flag.width <= 0)
        str_list[1] = NULL;
    else {
        str_struct->total_len += str_struct->current_flag.width;
        str_list[1] = my_calloc(str_struct->current_flag.width
            + 1, sizeof(char));
        for (int i = 0; i < str_struct->current_flag.width; i++)
            str_list[1][i] = ' ';
    }
    add_text(str_struct, str_list);
}
