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

/* Libmy C data structures */



    /* Enums */

/**
 * @enum my_bool
 * @brief A boolean type with more options than just true and false
 * @note This enum is especially used in memory functions
 */
typedef enum my_bool {
    NONE = -2,
    DEFAULT = -1,
    FALSE = 0,
    TRUE = 1
} my_bool_t;

/**
 * @enum type
 * @brief The type of a data
 * @note This enum is used to identify the type of data stored in a node
 */
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

/**
 * @enum logs_type_e
 * @brief The type of logs
 * @note This enum is used to identify the type of logs
 * and to display them in the console with colors
 */
typedef enum logs_type_e {
    LOGS_NONE = 0,    ///< No type
    LOGS_DEBUG = 1,   ///< Debug
    LOGS_WARNING = 2, ///< Warning
    LOGS_ERROR = 3    ///< Error
} logs_type_t;

/**
 * @enum separator_type
 * @brief The type of separator used in
 * the my_str_to_array and the my_str_to_word_array functions
 */
typedef enum separator_type {
    DEFAULT_SEPARATORS = 0, ///< DEFAULT SEPARATORS
    CHAR_SEPARATORS = 1,    ///< LIST OF CHAR SEPARATORS
    STRING_SEPARATORS = 2   ///< LIST OF STRING SEPARATORS
} separator_type_t;



    /* Aliases */

        /* Time */

typedef struct timespec timespec_t;


        /* Network */

typedef struct pollfd pollfd_t;
typedef struct sockaddr_in sockaddr_in_t;



    /* Unions and Structures */

        /* Linked list */

/**
 * @struct node_s
 * @brief A structure representing a node in a linked list
 */
typedef struct node_s {
    /** Pointer to the previous node */
    struct node_s *prev;
    /** Pointer to the data */
    void *data;
    /** Type of the data */
    type_t type;
    /** Pointer to the next node */
    struct node_s *next;
} node_t;


        /* Hash table */

/**
 * @struct hashtable_entry_s
 * @brief A structure representing an entry in a hash table
 */
typedef struct hashtable_entry_s {
    /** Pointer to the previous entry */
    struct hashtable_entry_s *prev;
    /** The key of the entry */
    int key;
    /** The value of the entry */
    char *value;
    /** Pointer to the next entry */
    struct hashtable_entry_s *next;
} hashtable_entry_t;

/**
 * @struct hashtable_s
 * @brief A structure representing a hash table
 */
typedef struct hashtable_s {
    /** The length of the table */
    size_t len;
    /** The hash function */
    ssize_t (*hash)(char *, size_t);
    /** The table of entries */
    hashtable_entry_t **table;
} hashtable_t;


        /* Garbage collector */

/**
 * @struct garbage_data_s
 * @brief A structure representing a data to be freed by the garbage collector
 */
typedef struct garbage_data_s {
    /** Pointer to the data */
    void *ptr;
    /** Function to free the data */
    void (*free_func)(void *);
} garbage_data_t;


        /* Logs */

/**
 * @struct point_s
 * @brief A structure representing a point in the code
 */
typedef struct point_s {
    /** The file name */
    const char *file;
    /** The line number */
    const int line;
    /** The function name */
    const char *func;
} point_t;


        /* Colors */

/**
 * @union color_rgb_u
 * @brief A union representing a color in ARGB format
 */
typedef union color_argb_u {
    /** The color */
    uint32_t color;
    struct {
        /** The alpha */
        uint8_t alpha;
        /** The red */
        uint8_t red;
        /** The green */
        uint8_t green;
        /** The blue */
        uint8_t blue;
    };
} color_argb_t;


        /* Vectors */

/**
 * @struct vector2s_s
 * @brief A structure representing a 2D vector with signed coordinates
 */
typedef struct vector2s_s {
    /** The x coordinate */
    ssize_t x;
    /** The y coordinate */
    ssize_t y;
} vector2s_t;

/**
 * @struct vector2u_s
 * @brief A structure representing a 2D vector with unsigned coordinates
 */
typedef struct vector2u_s {
    /** The x coordinate */
    size_t x;
    /** The y coordinate */
    size_t y;
} vector2u_t;

/**
 * @struct vector2d_s
 * @brief A structure representing a 2D vector with double coordinates
 */
typedef struct vector2d_s {
    /** The x coordinate */
    double x;
    /** The y coordinate */
    double y;
} vector2d_t;

/**
 * @struct vector3s_s
 * @brief A structure representing a 3D vector with signed coordinates
 */
typedef struct vector3s_s {
    /** The x coordinate */
    ssize_t x;
    /** The y coordinate */
    ssize_t y;
    /** The z coordinate */
    ssize_t z;
} vector3s_t;

/**
 * @struct vector3u_s
 * @brief A structure representing a 3D vector with unsigned coordinates
 */
typedef struct vector3u_s {
    /** The x coordinate */
    size_t x;
    /** The y coordinate */
    size_t y;
    /** The z coordinate */
    size_t z;
} vector3u_t;

/**
 * @struct vector3d_s
 * @brief A structure representing a 3D vector with double coordinates
 */
typedef struct vector3d_s {
    /** The x coordinate */
    double x;
    /** The y coordinate */
    double y;
    /** The z coordinate */
    double z;
} vector3d_t;


        /* Information structures */

/**
 * @struct info_param_s
 * @brief A structure representing the information of program parameters
 */
typedef struct info_param_s {
    /** The length of the string */
    size_t length;
    /** The string */
    char *str;
    /** The copy of the string */
    char *copy;
    /** The array of words */
    char **word_array;
} info_param_t;


        /* Get number */

/**
 * @struct number_settings_s
 * @brief A structure representing the settings of the my_get_number function
 */
typedef struct number_settings_s {
    /** Allow multiples signes in the string */
    bool multiple_signe;
    /** Allow letters before the number */
    bool letter_before;
    /** Allow letters after the number */
    bool letter_after;
    /** Allow overflow in the number */
    bool overflow;
} number_settings_t;

    /**
     * @brief The default settings for the my_get_number function
     */
    #define DEFAULT_NB ((number_settings_t) {false, false, false, false})


        /* String to array */

/**
 * @struct array_settings_s
 * @brief A structure representing the settings of the my_str_to_array function
 */
typedef struct array_settings_s {
    /** The type of the separator */
    separator_type_t type;
    /** The separator:\n
     * - For DEFAULT_SEPARATOR, you must leave it at null\n
     * - For LIST_SEPARATOR, it must be a string containing the separators\n
     * - For STRING_SEPARATOR, it must be an array of string
     * containing the string separators
     * */
    void *separator;
    /** The inhibitors who that cover a single character
     * example : \ */
    char *inhibitors_single;
    /** The inhibitors who that cover a large sequence
     * used once to open the sequence and again to close it
     * example : \", ' or ` */
    char *inhibitors_double;
} array_settings_t;

/**
 * @brief The default settings for the my_str_to_array function
 * @param type The type of the separator
 * @param separator The separator to use
 */
static inline array_settings_t my_default_array_settings(
    separator_type_t type, void *separator)
{
    return (array_settings_t) {
        type,
        separator,
        DEFAULT_INHIBITOR_SINGLE,
        DEFAULT_INHIBITOR_DOUBLE
    };
}

/**
 * @struct str_to_array_s
 * @brief A structure representing the data used
 * to convert a string to an array
 */
typedef struct str_to_array_s {
    /** The string to convert */
    const char *str;
    /** The settings of the conversion */
    array_settings_t settings;
    /** The number of words in the string */
    size_t nb_words;
    /** The size of the last separator found */
    size_t last_separator_size;
    /* The current inhibitor found */
    char inhibitor;
    /** The index of the last word found */
    size_t saved_index;
    /** The number of letters in the next word */
    size_t nb_letters;
    /** The list of characters of the next word */
    node_t *next_word;
    /** The array of words */
    char **array;
} str_to_array_t;

/**
 * @brief A function pointer type to check if a character is a separator
 * @param data The data used to convert the string to an array
 * @param index The index of the character to check
 * @return true if the character is a separator, false otherwise
 */
typedef bool (*is_separator_t)(str_to_array_t *, size_t);


        /* Create string (beta) */

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
    uint8_t flag_id;
    bool attributes[5];
    ssize_t width;
    bool precision;
    size_t precision_value;
    uint8_t specifier_id;
    char *sign;
} flag_t;

typedef struct format_s {
    char const *format_str;
    va_list format_list;
    size_t total_len;
    node_t *str_list;
    size_t current_index;
    flag_t current_flag;
    bool invalid_status;
} format_t;



    /* Global variables */

/**
 * @brief The global error number
 * @note This variable is used by:\n
 * - my_get_number
 */
extern int my_errno;

/**
 * @brief The list of separator functions used in the my_str_to_array function
 */
extern const is_separator_t is_separator[3];

/**
 * @brief The strings used to display the logs type
 */
extern const char *logs_type_strings[];

/***
 * @brief The colors used to display the logs type
 */
extern const char *logs_type_color[];

/**
 * @brief The list of format specifiers used in the my_create_str function
 */
extern const char *format_specifiers[];

#endif /* DATA_STRUCTURE_H_ */
