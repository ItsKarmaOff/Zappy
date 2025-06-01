/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The header file for the data structures
*/
/**
 * @file data_structure.h
 * @brief The header file for the data structures
 * @author Nicolas TORO
 */

#ifndef DATA_STRUCTURE_H_
    #define DATA_STRUCTURE_H_

    #include "constants.h"

/* A reproduction of the boolean */
typedef enum my_bool {
    NONE = -2, /* NONE */
    DEFAULT = -1, /* DEFAULT */
    FALSE = 0, /* FALSE */
    TRUE = 1 /* TRUE */
} my_bool_t;

extern int my_errno; /* The error number */

/* The information of the my_params_to_array */
struct info_param {
    int length; /*The length of the string */
    char *str; /* The string */
    char *copy; /* The copy of the string */
    char **word_array; /* The array of words */
};

/* The decomposed color */
typedef union color_argb_u {
    uint32_t color; /* The color */
    struct {
        uint8_t alpha; /* The alpha */
        uint8_t red; /* The red */
        uint8_t green; /* The green */
        uint8_t blue; /* The blue */
    };
} color_argb_t;

/* The separator type of the my_str_to_word_array */
typedef enum separator_type {
    DEFAULT_SEPARATOR, /* DEFAULT SEPARATORS */
    LIST_SEPARATOR, /* LIST OF SEPARATORS */
    STRING_SEPARATOR /* STRING SEPARATOR */
} separator_type_t;

/* The settings of the my_get_number */
typedef struct number_settings_s {
    my_bool_t multiple_signe; /* Allow multiples signes in the string */
    my_bool_t letter_before; /* Allow letters before the number */
    my_bool_t letter_after; /* Allow letters after the number */
    my_bool_t overflow; /* Allow overflow in the number */
} number_settings_t;

    #define NB number_settings_t

/* Enum for the type of the data */
typedef enum type {
    SIGNED_CHAR,
    SHORT,
    INT,
    LONG,
    LONG_LONG,
    UNSIGNED_CHAR,
    UNSIGNED_SHORT,
    UNSIGNED_INT,
    UNSIGNED_LONG,
    UNSIGNED_LONG_LONG,
    SIZE_T,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE,
    CHAR,
    STRING,
    ARRAY_OF_STRING,
    VOID,
    UNKNOWN
} type_t;

/* Node of the linked list */
typedef struct node_s {
    struct node_s *prev; /* Pointer to the previous node */
    void *data; /* Pointer to the data */
    type_t type; /* Type of the data */
    struct node_s *next; /* Pointer to the next node */
} node_t;

/* The table of a hashtable */
typedef struct hashtable_entry_s {
    struct hashtable_entry_s *prev; /* Pointer to the previous entry */
    int key; /* The key of the entry */
    char *value; /* The value of the entry */
    struct hashtable_entry_s *next; /* Pointer to the next entry */
} hashtable_entry_t;

/* The hashtable structures */
typedef struct hashtable_s {
    int len; /* The length of the table */
    int (*hash)(char *, int); /* The hash function */
    hashtable_entry_t **table; /* The table */
} hashtable_t;

/* The garbage data structure */
typedef struct garbage_data_s {
    void *ptr; /* Pointer to the data */
    void (*free_func)(void *); /* Function to free the data */
} garbage_data_t;

/* The point structure */
typedef struct point_s {
    const char *file; /* The file name */
    const int line; /* The line number */
    const char *func; /* The function name */
} point_t;

/* The logs type enumeration */
typedef enum logs_type_e {
    LOGS_NONE = 0, /* No type */
    LOGS_DEBUG = 1, /* Debug */
    LOGS_WARNING = 2, /* Warning */
    LOGS_ERROR = 3 /* Error */
} logs_type_t;

/* The logs type strings */
extern const char *logs_type_strings[];

/* The logs type colors */
extern const char *logs_type_color[];

typedef union my_double_s {
    double value;
    struct {
        uint64_t mantissa : DBL_MANT_DIG;
        uint16_t exponent : 11;
        uint8_t sign : 1;
    } parts;
} my_double_t;

typedef union my_long_double_s {
    long double value;
    struct {
        uint64_t mantissa : LDBL_MANT_DIG;
        uint16_t exponent : 15;
        uint8_t sign : 1;
    } parts;
} my_long_double_t;

typedef struct flag_s {
    int flag_id;
    bool attributes[5];
    int width;
    bool precision;
    int precision_value;
    int specifier_id;
    char *sign;
} flag_t;

typedef struct format_s {
    char const *format_str;
    va_list format_list;
    intmax_t total_len;
    node_t *str_list;
    int current_index;
    flag_t current_flag;
    int status;
} format_t;

extern const char *format_specifiers[];

#endif /* DATA_STRUCTURE_H_ */
