/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_create_str function
*/
/**
 * @file my_create_str.c
 * @brief The file containing the my_create_str function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

const char *format_specifiers[] =
{"hh", "h", "ll", "l", "j", "z", "t", "L", NULL};

/**
 * @brief Apply the flags to the string
 * @param str_struct The structure containing the string and the flags
 * @return <b>void</b>
 * @author Nicolas TORO
 */
static void apply_flags(format_t *str_struct)
{
    void (*flags_functions[])(format_t *str_struct) = {
        NULL, &flag_lowercase_a, &flag_lowercase_b, &flag_lowercase_c,
        &flag_lowercase_d, &flag_lowercase_e, &flag_lowercase_f,
        &flag_lowercase_g, &flag_lowercase_i, &flag_lowercase_m,
        &flag_lowercase_n, &flag_lowercase_o, &flag_lowercase_p,
        &flag_lowercase_s, &flag_lowercase_u, &flag_lowercase_x,
        &flag_percent, &flag_uppercase_a, &flag_uppercase_e,
        &flag_uppercase_f, &flag_uppercase_g, &flag_uppercase_n,
        &flag_uppercase_s, &flag_uppercase_x,
    };

    flags_functions[str_struct->current_flag.flag_id](str_struct);
}

static void show_format(format_t *str_struct)
{
    my_putstr("FORMAT:\n");
    my_putstr("STRING: ");
    my_putstr(str_struct->format_str);
    my_putstr("\nFLAG: ");
    my_putchar(FORMAT_FLAGS[str_struct->current_flag.flag_id - 1]);
    my_putstr("\nATTRIBUTES: ");
    for (int i = 0; i < 5; i++) {
        if (str_struct->current_flag.attributes[i] == true)
            my_putchar(FORMAT_ATTRIBUTES[i]);
    }
    my_putstr("\nWIDTH: ");
    my_putnbr(str_struct->current_flag.width);
    if (str_struct->current_flag.precision) {
        my_putstr("\nPRECISION: ");
        my_putnbr(str_struct->current_flag.precision_value);
    }
    my_putstr("\nSPECIFIER: ");
    my_putstr(format_specifiers[str_struct->current_flag.specifier_id - 1]);
    my_putchar('\n');
}

static void find_format_specifier(format_t *str_struct)
{
    str_struct->current_flag.specifier_id = 0;
    for (int index = 0; format_specifiers[index] != NULL; index++) {
        if (my_strncmp(&FORMAT_CHAR, format_specifiers[index],
        my_strlen(format_specifiers[index])) == 0) {
            str_struct->current_flag.specifier_id = index + 1;
            str_struct->current_index += my_strlen(format_specifiers[index]);
            return;
        }
    }
}

static void find_format_informations(format_t *str_struct)
{
    for (; FORMAT_CHAR != '\0' && my_char_is(FORMAT_CHAR, FORMAT_ATTRIBUTES);
    str_struct->current_index++) {
        str_struct->current_flag.attributes[
            my_get_char_index(FORMAT_ATTRIBUTES, FORMAT_CHAR, 1)] = true;
    }
    for (; FORMAT_CHAR != '\0' && my_char_is(FORMAT_CHAR, FORMAT_NUMBERS);
    str_struct->current_index++) {
        str_struct->current_flag.width *= 10;
        str_struct->current_flag.width += FORMAT_CHAR - '0';
    }
    if (FORMAT_CHAR == '.') {
        str_struct->current_flag.precision = true;
        str_struct->current_index++;
    }
    for (; FORMAT_CHAR != '\0' && my_char_is(FORMAT_CHAR, FORMAT_NUMBERS);
    str_struct->current_index++) {
        str_struct->current_flag.precision_value *= 10;
        str_struct->current_flag.precision_value += FORMAT_CHAR - '0';
    }
    find_format_specifier(str_struct);
}

static void invalid_flag(format_t *str_struct)
{
    for (int index = 0; index < 5; index++) {
        if (str_struct->current_flag.attributes[index] == true) {
            my_push_back(&str_struct->str_list,
                my_strndup(&FORMAT_ATTRIBUTES[index], 1), STRING);
            str_struct->total_len++;
        }
    }
    if (str_struct->current_flag.width != 0) {
        my_push_back(&str_struct->str_list, my_nbr_to_str_unsigned(str_struct->
            current_flag.width, BASE_10, sizeof(uint)), STRING);
        str_struct->total_len += my_nbrlen(str_struct->current_flag.width);
    }
    if (str_struct->current_flag.precision) {
        my_push_back(&str_struct->str_list, my_strndup(".", 1), STRING);
        my_push_back(&str_struct->str_list, my_nbr_to_str_unsigned(str_struct->
            current_flag.precision_value, BASE_10, sizeof(uint)), STRING);
        str_struct->total_len +=
            my_nbrlen(str_struct->current_flag.precision_value) + 1;
    }
}

static void find_flag(format_t *str_struct)
{
    str_struct->current_index += 1;
    find_format_informations(str_struct);
    for (; str_struct->current_flag.flag_id < NB_FLAGS;
    str_struct->current_flag.flag_id++) {
        if (FORMAT_CHAR == FORMAT_FLAGS[str_struct->current_flag.flag_id]) {
            str_struct->current_flag.flag_id += 1;
            return;
        }
    }
    my_push_back(&str_struct->str_list, my_strndup("%", 1), STRING);
    str_struct->total_len++;
    invalid_flag(str_struct);
    str_struct->current_index--;
}

static void fill_str_struct(format_t *str_struct)
{
    if (str_struct->format_str == NULL) {
        str_struct->status = -1;
        return;
    }
    for (; FORMAT_CHAR != '\0'; str_struct->current_index++) {
        if (FORMAT_CHAR == '%')
            find_flag(str_struct);
        if (str_struct->current_flag.flag_id != 0)
            apply_flags(str_struct);
        else {
            my_push_back(&str_struct->str_list,
                my_strndup(&FORMAT_CHAR, 1), STRING);
            str_struct->total_len++;
        }
        if (str_struct->status != 0)
            return;
        str_struct->current_flag = (flag_t){0};
    }
}

/**
 * @brief The function that creates a string with the given format and args
 * @param format The string to format
 * @param args The list of args to insert in the string
 * @return <b>char*</b> The formatted string
 * @author Nicolas TORO
 */
char *my_create_str_va(const char *format, va_list args)
{
    format_t str_struct = {.format_str = format};
    char *result_str = NULL;
    my_bool_t malloc_backup = malloc_state(NONE);
    my_bool_t tmp_malloc_backup = tmp_malloc_state(NONE);

    tmp_malloc_state(DEFAULT);
    malloc_state(FALSE);
    va_copy(str_struct.format_list, args);
    fill_str_struct(&str_struct);
    tmp_malloc_state(tmp_malloc_backup);
    malloc_state(malloc_backup);
    if (str_struct.status != 0) {
        my_delete_list(&str_struct.str_list);
        return NULL;
    }
    result_str = my_calloc(str_struct.total_len + 1, sizeof(char));
    for (node_t *tmp = str_struct.str_list; tmp != NULL; tmp = tmp->next)
        my_strcat(result_str, tmp->data);
    my_delete_list(&str_struct.str_list);
    return result_str;
}

/**
 * @brief The function that creates a string with the given format and args
 * @param format The string to format
 * @param ... The list of args to insert in the string
 * @return <b>char*</b> The formatted string
 * @author Nicolas TORO
 */
char *my_create_str(const char *format, ...)
{
    va_list args;
    char *result_str = NULL;

    va_start(args, format);
    result_str = my_create_str_va(format, args);
    va_end(args);
    return result_str;
}
