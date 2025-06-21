/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The header file for the functions
*/
/**
 * @file functions.h
 * @brief The header file for the functions
 * @author Nicolas TORO
 */

#ifndef FUNCTIONS_H_
    #define FUNCTIONS_H_

    #include "data_structures.h"

/* Libmy C functions */


    /* Array functions */

/**
 * @brief Returns the length of an array (array)
 * @param array The array to check
 * @return <b>size_t</b> The length of the array
 * @author Nicolas TORO
 */
size_t my_array_len(void **array);

/**
 * @brief Sorts an array (array) with a defined size (size)
 * of integers in ascending order
 * @param tab The array to sort
 * @param size The size of the tab
 * @author Nicolas TORO
 */
void my_sort_int_array(int *array, size_t size);

/**
 * @brief Returns an array of words delimited
 * by a separator (array_settings.separator) from a string (str)
 * @note Compared to my_str_to_word_array,
 * this function will use an array_settings to personalize the conversion
 * @param str The string to convert
 * @param array_settings The settings for the convertion
 * @return <b>char**</b> The array of words
 * @author Nicolas TORO
 */
char **my_str_to_array(const char *str, array_settings_t array_settings);

/**
 * @brief Returns an array of words delimited
 * by a separator (separator) from a string (str)
 * @param str The string to convert
 * @param type The type of separator
 * @param separator The separator to use
 * @return <b>char**</b> The array of words
 * @author Nicolas TORO
 */
char **my_str_to_word_array(const char *str,
    separator_type_t type, const char *separator);

/**
 * @brief Returns the length of an word array (array)
 * @param array The array to check
 * @param nb_str The number of strings in the array
 * @param stop_at_null If true,
 * the function will stop counting at the first NULL
 * @return <b>size_t</b> The length of the word array
 * @author Nicolas TORO
 */
size_t my_word_array_len(char **array, size_t nb_str, bool stop_at_null);

/**
 * @brief Converts an array of words to a string
 * @param word_array The array of words to convert
 * @param separator The separator to use between words
 * @return <b>char *</b> The string containing the words
 */
char *my_word_array_to_str(char **word_array, const char *separator);



    /* Calculs functions */

/**
 * @brief Returns the factorial of a number (nb)
 * @note Returns 0 if the number is negative or greater than 12
 * @param nb The number to calculate
 * @return <b>int64_t</b> The factorial of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_factorial(intmax_t nb);

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>intmax_t</b> The power of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_power(intmax_t nb, intmax_t p);

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>double</b> The power of the number
 * @author Nicolas TORO
 */
double my_compute_power_double(double nb, double p);

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>float</b> The power of the number
 * @author Nicolas TORO
 */
float my_compute_power_float(float nb, float p);

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>long double</b> The power of the number
 * @author Nicolas TORO
 */
long double my_compute_power_long_double(long double nb, long double p);

/**
 * @brief Returns the square root of a number (nb)
 * @param nb The number to calculate
 * @return <b>intmax_t</b> The square root of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_square_root(intmax_t nb);

/**
* @brief Returns the previous prime number before a number (nb)
* @param nb The number to check
* @return <b>intmax_t</b> The previous prime number before the number
* or the number if it is prime
* @author Nicolas TORO
*/
intmax_t my_find_prime_inf(intmax_t nb);

/**
 * @brief Returns the next prime number after a number (nb)
 * @param nb The number to check
 * @return <b>intmax_t</b> The next prime number after the number
 * or the number if it is prime
 * @author Nicolas TORO
 */
intmax_t my_find_prime_sup(intmax_t nb);

/**
 * @brief Returns 1 if the number (nb) is prime and 0 otherwise
 * @param nb The number to check
 * @return <b>bool</b> <u>1</u> if the number is prime, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_is_prime(intmax_t nb);

/**
 * @brief Rounds a double to a certain precision
 * @param nb The number to round
 * @param precision The precision to round to
 * @return <b>double</b> The rounded number
 * @author Nicolas TORO
 */
double my_round_double(double nb, double precision);

/**
 * @brief Rounds a double to a certain precision
 * @param nb The number to round
 * @param precision The precision to round to
 * @return <b>float</b> The rounded number
 * @author Nicolas TORO
 */
float my_round_float(float nb, float precision);

/**
 * @brief Rounds a double to a certain precision
 * @param nb The number to round
 * @param precision The precision to round to
 * @return <b>long double</b> The rounded number
 * @author Nicolas TORO
 */
long double my_round_long_double(long double nb, long double precision);

/**
 * @brief Split a double into an integer part and a decimal part
 * @param value The value to split
 * @param integer_part The integer part
 * @return <b>double</b> The decimal part
 */
double my_split_double(double value, double *integer_part);

/**
 * @brief Split a double into an integer part and a decimal part
 * @param value The value to split
 * @param integer_part The integer part
 * @return <b>double</b> The decimal part
 */
long double my_split_long_double(long double value, long double *integer_part);
double my_trunc(double value);


    /* Char functions */

/**
* @brief Adds a char (chr) at the end of a string (str)
* @note The string must be allocated and have enough space
* @param str The string to modify
* @param chr The char to add
* @return <b>char *</b> The modified string
* @author Nicolas TORO
*/
char *my_add_chr(char *str, char chr);

/**
 * @brief Checks if a char (c) is in a list of chars (char_list)
 * @param c The char to check
 * @param char_list The list of chars to check
 * @return <b>int</b> <u>1</u> if the char is in the list, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is(char c, const char *char_list);

/**
 * @brief Checks if a char (c) is a letter
 * @param c The char to check
 * @return <b>bool</b> <u>1</u> if the char is a letter, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is_alpha(char c);

/**
 * @brief Checks if a char (c) is a number
 * @param c The char to check
 * @return <b>bool</b> <u>1</u> if the char is a number, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is_num(char c);

/**
 * @brief Checks if a char (c) is printable
 * @param c The char to check
 * @return <b>bool</b> <u>1</u> if the char is printable, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is_printable(char c);

/**
 * @brief Get the index of a char in a str according to its occurrence
 * @note The first occurrence is 1, the second is 2, etc.
 * @param str The string to check
 * @param c The letter to find
 * @param occurrence The occurrence of the letter to find
 * @return <b>ssize_t</b> <u>-1</u> if the letter is not found, otherwise
 * the index of the letter in the string
 */
ssize_t my_get_char_index(const char *str, char c, size_t occurrence);

/**
 * @brief Returns the last char of a string (str)
 * @param str The string to check
 * @return <b>char</b> The last char of the string
 * @author Nicolas TORO
 */
char my_get_last_char(char *str);

/**
 * @brief Replace a char in a string by another char
 * @param str The string to modify
 * @param to_replace The char to replace
 * @param replace_by The char to replace by
 * @return <b>void</b>
 */
void my_replace_char(char *str, char to_replace, char replace_by);

/**
 * @brief Replace a char in a string by another char at a specific occurrence
 * @param str The string to modify
 * @param to_replace The char to replace
 * @param replace_by The char to replace by
 * @param occurrence The occurrence of the char to replace
 * @return <b>void</b>
 */
void my_replace_char_at(char *str, char to_replace, char replace_by,
    size_t occurrence);



    /* Hash functions */

/**
* @brief Creates a hashtable
* @param hash The hash function to use
* @param len The length of the hashtable
* @return <b>hashtable_t*</b> The created hashtable
* @author Nicolas TORO
*/
hashtable_t *my_create_hashtable(ssize_t (*hash)(char *, size_t), size_t len);

/**
 * @brief Deletes a hashtable
 * @param ht The hashtable to delete
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_hashtable(hashtable_t *ht);

/**
 * @brief A simple hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>ssize_t</b> The hash value
 */
ssize_t my_hash_simple(char *key, size_t len);

/**
 * @brief A djb2 hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>ssize_t</b> The hash value
 */
ssize_t my_hash_djb2(char *key, size_t len);

/**
 * @brief A p256 hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>ssize_t</b> The hash value
 */
ssize_t my_hash_p256(char *key, size_t len);

/**
 * @brief A custom hash function
 * @param key The key to hash
 * @param len The length of the key
 * @return <b>ssize_t</b> The hash value
 */
ssize_t my_hash(char *key, size_t len);

/**
 * @brief Deletes a key in a hashtable
 * @param ht The hashtable
 * @param key The key to delete
 * @return <b>bool</b> <u>false</u> if failure, <u>true</u> if success
 * @author Nicolas TORO
 */
bool my_ht_delete(hashtable_t *ht, char *key);

/**
 * @brief Dumps (display) a hashtable
 * @param ht The hashtable to dump
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_ht_dump(hashtable_t *ht);

/**
 * @brief Inserts a key-value pair in a hashtable
 * @param ht The hashtable
 * @param key The key to insert
 * @param value The value to insert
 * @return <b>bool</b> <u>false</u> if failure, <u>true</u> if success
 * @author Nicolas TORO
 */
bool my_ht_insert(hashtable_t *ht, char *key, char *value);

/**
 * @brief Searches a key in a hashtable
 * @param ht The hashtable
 * @param key The key to search
 * @return <b>char*</b> The value of the key if found, NULL otherwise
 * @author Nicolas TORO
 */
char *my_ht_search(hashtable_t *ht, char *key);



    /* List functions */

/**
 * @brief Concatenates two linked lists
 * @param begin1 The beginning of the first list
 * @param begin2 The beginning of the second list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_concat_list(node_t **begin1, node_t *begin2);

/**
 * @brief Deletes a circular linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_circle_list(node_t **begin);

/**
 * @brief Deletes the linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_list(node_t **begin);

/**
 * @brief Deletes nodes from a linked list
 * @param begin The beginning of the list
 * @param data_ref The data to delete
 * @param cmp The comparison function
 * @return <b>size_t</b> The number of nodes deleted from the list
 * @author Nicolas TORO
 */
size_t my_delete_nodes(node_t **begin, void const *data_ref, int (*cmp)());

/**
 * @brief Finds a node in the linked list
 * @param begin The beginning of the list
 * @param data The data to find
 * @param cmp The comparison function
 * @return <b>node_t *</b> The node found in the list
 * @author Nicolas TORO
 */
node_t *my_find_node(node_t const *begin, void const *data_ref, int (*cmp) ());

/**
 * @brief Gets the node at the specified index in a linked list
 * @param begin The beginning of the list
 * @param index The index of the node to get
 * @return <b>node_t *</b> The node at the specified index or NULL if not found
 * @author Nicolas TORO
 */
node_t *my_get_node_at_index(node_t *begin, size_t index);

/**
 * @brief Returns the size of the linked list
 * @param begin The beginning of the list
 * @return <b>size_t</b> The size of the list
 * @author Nicolas TORO
 */
size_t my_list_size(node_t const *begin);

/**
 * @brief Returns the size of the linked list
 * @param begin The beginning of the list
 * @return <b>size_t</b> The size of the list
 * @author Nicolas TORO
 */
size_t my_list_size_circled(node_t const *begin);

/**
 * @brief Converts the linked list to an array
 * @param list The linked list to convert
 * @return <b>void **</b> The array created from the linked list
 * @author Nicolas TORO
 */
void **my_list_to_array(node_t *list);

/**
 * @brief Converts the circular linked list to an array
 * @param list The circular linked list to convert
 * @return <b>void **</b> The array created from the circular linked list
 */
void **my_list_to_array_circled(node_t **list);

/**
 * @brief Merges two linked lists
 * @param begin1 The beginning of the first list
 * @param begin2 The beginning of the second list
 * @param cmp The comparison function
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_merge_list(node_t **begin1, node_t *begin2, int (*cmp)());

/**
 * @brief Creates a linked list from the arguments (argc and argv)
 * @param ac The number of arguments
 * @param av The array of arguments
 * @return <b>node_t *</b> The linked list created from the array of strings
 * @author Nicolas TORO
 */
node_t *my_params_to_list(int ac, char *const *av);

/**
 * @brief Removes the last node of the list
 * @param begin The beginning of the list
 * @return <b>node_t *</b> The last node of the list
 * @author Nicolas TORO
 */
node_t *my_pop_back(node_t **begin);

/**
 * @brief Removes the first node of the list
 * @param begin The beginning of the list
 * @return <b>node_t *</b> The first node of the list
 * @author Nicolas TORO
 */
node_t *my_pop_front(node_t **begin);

/**
 * @brief Removes a node from the list
 * @param begin The beginning of the list
 * @param data_ref The data to remove
 * @param cmp The comparison function
 * @return <b>node_t *</b> The node removed from the list
 * @author Nicolas TORO
 */
node_t *my_pop_node(node_t **begin, void const *data_ref, int (*cmp)());

/**
 * @brief Skip a node in a linked list and
 * change the previous node to the next node
 * @param head The beginning of the list
 * @param to_delete The node to skip
 * @return <b>node_t *</b> The to_delete node
 * @author Gianni TUERO
 */
node_t *my_previous_to_next(node_t **head, node_t *to_delete);

/**
 * @brief Adds a node at the end of the list
 * @param begin The beginning of the list
 * @param data The data to add
 * @param type The type of the data
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_push_back(node_t **begin, void *data, type_t type);

/**
* @brief Adds a node at the beginning of the circular linked list
* @param begin The beginning of the list
* @param data The data to add
* @param type The type of the data
* @return <b>void</b>
*/
void my_push_back_circled(node_t **begin, void *data, type_t type);

/**
* @brief Adds a node at the beginning of the list
* @param begin The beginning of the list
* @param data The data to add
* @param type The type of the data
* @return <b>void</b>
* @author Nicolas TORO
*/
void my_push_front(node_t **begin, void *data, type_t type);

/**
 * @brief Reverses the linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_rev_list(node_t **begin);

/**
 * @brief Sorts the linked list
 * @param begin The beginning of the list
 * @param cmp The comparison function
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_sort_list(node_t **begin, int (*cmp)());



    /* Memory functions */

/**
 * @brief Adds a pointer to the garbage collector
 * @note The pointer is added to the garbage collector
 * @param add The status of the garbage
 * <u>true</u> to add the pointer and <u>false</u> to remove it
 * @param ptr The pointer to add
 * @param free_func The function to free the pointer
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_add_to_garbage(bool add, void *ptr, void (*free_func)(void *));

/**
* @brief Allocates memory and initializes all the bytes to 0
* @param element_count The number of elements
* @param element_size The size of each element
* @return <b>void *</b> A pointer to the allocated memory
* @author Nicolas TORO
*/
void *my_calloc(size_t element_count, size_t element_size);

/**
 * @brief Closes a file descriptor (fd)
 * @note Used for the garbage collector
 * @param fd The file descriptor to close
 */
void my_close(void *fd);

/**
 * @brief Exits the program
 * @note An ASM function called by the my_exit function
 * @param status The status to return
 * @return <b>void</b>
 */
extern void my_exit_asm(int status);

/**
* @brief Exits the program
* @param status The status to return
* @param message The message to display
* @return <b>void</b>
* @author Nicolas TORO
*/
void my_exit(int status, char *message);

/**
 * @brief Free allocated memory in the garbage collector
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_free(void);

/**
 * @brief Frees an array (array)
 * @param array The array to free
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_free_array(void **array);

/**
 * @brief Frees a pointer (ptr)
 * @param ptr The pointer to free
 * @return <b>void *</b> Always <u>NULL</u>
 * @author Nicolas TORO
 */
void *my_free_ptr(void *ptr);

/**
 * @brief Allocates memory for an array of bytes (size)
 * @note The allocation type is defined by the malloc state,
 * or by the temporary malloc state if it is defined
 * @param size The size of the memory to allocate
 * @return <b>void *</b> A pointer to the allocated memory
 * @author Nicolas TORO
 */
void *my_malloc(size_t size);

/**
 * @brief Searches for the first occurrence of the character (c)
 * in the first (n) bytes of the string (s)
 * @param memory_block The memory block to search in
 * @param searched_char The character to search
 * @param size The size of the memory block
 * @return <b>void *</b> A pointer to the first occurrence of the character
 * in the memory block if found, NULL otherwise
 * @author Nicolas TORO
 */
void *my_memchr(const void *memory_block, int searched_char, size_t size);

/**
 * @brief Compares the first (size) bytes
 * of the memory areas (pointer1) and (pointer2)
 * @param pointer1 The first memory area
 * @param pointer2 The second memory area
 * @param size The number of bytes to compare
 * @return <b>int</b> 0 if the memory areas are equal,
 * a positive value if the first different byte in (pointer1) is greater than
 * the corresponding byte in (pointer2), a negative value otherwise
 * @author Nicolas TORO
 */
int my_memcmp(const void *pointer1, const void *pointer2, size_t size);

/**
 * @brief Copies (size) bytes from memory area (source)
 * to another memory area (destination)
 * @param destination The destination memory area
 * @param source The source memory area
 * @param size The number of bytes to copy
 * @return <b>void *</b> A pointer to the destination memory area
 * @author Nicolas TORO
 */
void *my_memcpy(void *destination, const void *source, size_t size);

/**
 * @brief Move (size) bytes from memory area (source)
 * to another memory area (destination)
 * @param destination The destination memory area
 * @param source The source memory area
 * @param size The number of bytes to move
 * @return <b>void *</b> A pointer to the destination memory area
 * @author Nicolas TORO
 */
void *my_memmove(void *destination, const void *source, size_t size);

/**
 * @brief Fills the first (size) bytes of the memory area pointed (pointer)
 * with a constant byte (value)
 * @param pointer The memory area to fill
 * @param value The byte to fill the memory area with
 * @param size The number of bytes to fill
 * @return <b>void *</b> A pointer to the memory area
 * @author Nicolas TORO
 */
void *my_memset(void *pointer, int value, size_t size);

/**
 * @brief Destroys the program by calling the provided destroy function
 * @note If the destroy function is NULL,
 * it will call the destroy function set previously.
 * If the program is already destroyed, it will do nothing.
 * @param destroy_func The function to call to destroy the program
 * @author Nicolas TORO
 */
void my_program_destroy(void (*destroy_func)(void *ptr));

/**
 * @brief Reallocates memory block
 * @param pointer The pointer to the memory block
 * @param size The new size of the memory block
 * @return <b>void *</b> A pointer to the new memory block
 * @author Nicolas TORO
 */
void *my_realloc(void *pointer, size_t size);

/**
 * @brief Resize an allocated memory block.
 * @param ptr Pointer to the previously allocated memory block.
 * @param old_size Size of the previously allocated memory block.
 * @param new_size New size for the memory block.
 * @return Pointer to the resized memory block, or NULL if new_size is 0.
 */
void *my_resize_alloc(void *ptr, size_t old_size, size_t new_size);

/**
 * @brief The temporary malloc state variable
 * @note NONE (-2): Returns just the value | DEFAULT (-1): Disable the priority
 * | FALSE (0): Basic malloc | TRUE (1): Save in garbage
 * @param set The new temporary malloc state
 * @return <b>my_bool_t</b> The temporary malloc state
 * @author Nicolas TORO
 */
my_bool_t tmp_malloc_state(my_bool_t set);

/**
 * @brief Updates the temporary malloc state
 * @param type The new temporary malloc state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_alloc(my_bool_t type);

/**
 * @brief The malloc state variable
 * @note NONE (-2): Returns just the value | DEFAULT (-1): Free all
 * | FALSE (0): Basic malloc | TRUE (1): Save in garbage
 * @param set The new malloc state
 * @return <b>my_bool_t</b> The malloc state
 * @author Nicolas TORO
 */
my_bool_t malloc_state(my_bool_t set);

/**
 * @brief Updates the malloc state
 * @param type The new malloc state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_malloc(my_bool_t type);



    /* Number functions */

/**
* @brief Returns the result of the conversion of a number (nbr)
* in a specific base (base_from) to another base (base_to)
* @param nbr The number to convert
* @param base_from The base of the number
* @param base_to The base to convert the number
* @return <b>char*</b> The converted number in the new base
* @author Nicolas TORO
*/
char *my_convert_base_signed(char const *nbr,
    char const *base_from, char const *base_to);

/**
 * @brief Returns the result of the conversion of a unsigned number (nbr)
 * in a specific base (base_from) to another base (base_to)
 * @param nbr The number to convert
 * @param base_from The base of the number
 * @param base_to The base to convert the number
 * @return <b>char*</b> The converted number in the new base
 * @author Nicolas TORO
 */
char *my_convert_base_unsigned(char const *nbr,
    char const *base_from, char const *base_to);

/**
 * @brief Returns an int number starting from a string number (number)
 * and change my_errno if an error occurs depending on the settings (settings)
 * @note The function will change <u>my_errno</u> by 1 if an error occurs
 * depending on the settings you choose with the <b>settings</b> parameter
 * @param number The string to convert
 * @param settings The settings of the function
 * @return <b>intmax_t</b> The number found in the string
 * @author Nicolas TORO
 */
intmax_t my_get_number(char *number, number_settings_t settings);

/**
 * @brief Returns a number starting from a string number (str)
 * in the requested base (base)
 * @note Returns 0 if the string is not a number
 * @note The function accept multiple signes in the string
 * @param str The string to convert
 * @param base The base of the number
 * @return <b>int64_t</b> The number found in the string
 * @author Nicolas TORO
 */
intmax_t my_getnbr_base(char const *str, char const *base);

/**
 * @brief Returns a float number starting from a string number (str)
 * @note Returns 0 if the string is not a number
 * @note The function accept only -0123456789.
 * @note The function accept only one point in the string
 * @param str The string to convert
 * @return <b>float</b> The number found in the string
 * @author Nicolas TORO
 */
float my_getnbr_float(char const *str);

/**
 * @brief Check if the number is inf
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is inf, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isinf_double(double nb);

/**
 * @brief Check if the number is inf
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is inf, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isinf_long_double(long double nb);

/**
 * @brief Check if the number is NaN
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is NaN, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isnan_double(double nb);

/**
 * @brief Check if the number is NaN
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is NaN, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isnan_long_double(long double nb);

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param precision The precision of the number
 * @param decimal_point The decimal point
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_double_to_str(double nbr, intmax_t precision, bool decimal_point);

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param precision The precision of the number
 * @param decimal_point The decimal point
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_double_to_str_exponent(double nbr, intmax_t precision,
    bool decimal_point);

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param precision The precision of the number
 * @param decimal_point The decimal point
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_long_double_to_str(long double nbr, intmax_t precision,
    bool decimal_point);

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param base The base to convert the number
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_to_str_signed(int64_t nbr, char const *base);

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param base The base to convert the number
 * @param type_size The size of the type of the number
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_to_str_unsigned(size_t nbr, char const *base,
    size_t type_size);

/**
 * @brief Returns the length of a number (nb)
 * @param nb The number to check
 * @return <b>size_t</b> The length of the number
 * @author Nicolas TORO
 */
size_t my_nbrlen(intmax_t nb);

/**
 * @brief Returns the result of the conversion of a size_t number (nbr)
 * in a specific base (base_from) to another base (base_to)
 * @param nbr The number to convert
 * @param base_from The base of the number
 * @param base_to The base to convert the number
 * @return <b>char*</b> The converted number in the new base
 * @author Nicolas TORO
 */
void my_round_float_str(char *float_nb, char last_char, int i, int enable);

/**
 * @brief Swaps two integers (a) and (b)
 * @param a The first integer
 * @param b The second integer
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_swap(int *a, int *b);

/**
 * @brief Swap the endian of a color
 * @param color The color to swap
 * @return <b>uint32_t</b> The color with the endian swapped
 * @author Nicolas TORO
 */
uint32_t my_swap_endian_color(uint32_t color);



    /* Params functions */

/**
* @brief Returns a string with all the arguments (argc and argv) concatenated
* @param argc The number of parameters
* @param argv The array of parameters
* @return <b>char*</b> The concatenated string of the parameters
* @author Nicolas TORO
*/
char *my_concat_params(int argc, char **argv);

/**
 * @brief Returns a info_param struct of the argc (ac) and the argv (av)
 * @param ac The number of parameters
 * @param av The array of parameters
 * @return <b>info_param_t *</b> The information of the parameters
 * @author Nicolas TORO
 */
info_param_t *my_params_to_array(int ac, char **av);

/**
 * @brief Prints all the parameters of the program
 * @param argc The number of parameters
 * @param argv The array of parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_print_params(int argc, char **argv);

/**
 * @brief Prints all the arguments (argc and argv) in reverse order
 * @param par The information of the parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_rev_params(int argc, char **argv);

/**
 * @brief Sorts the parameters (argc and argv) in ascending order
 * @param argc The number of parameters
 * @param argv The array of parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_sort_params(int argc, char **argv);


/* Flag functions */
void flag_lowercase_a(format_t *str_struct);
void flag_lowercase_b(format_t *str_struct);
void flag_lowercase_c(format_t *str_struct);
void flag_lowercase_d(format_t *str_struct);
void flag_lowercase_e(format_t *str_struct);
void flag_lowercase_f(format_t *str_struct);
void flag_lowercase_g(format_t *str_struct);
void flag_lowercase_i(format_t *str_struct);
void flag_lowercase_m(format_t *str_struct);
void flag_lowercase_n(format_t *str_struct);
void flag_lowercase_o(format_t *str_struct);
void flag_lowercase_p(format_t *str_struct);
void flag_lowercase_s(format_t *str_struct);
void flag_lowercase_u(format_t *str_struct);
void flag_lowercase_x(format_t *str_struct);
void flag_percent(format_t *str_struct);
void flag_uppercase_a(format_t *str_struct);
void flag_uppercase_e(format_t *str_struct);
void flag_uppercase_f(format_t *str_struct);
void flag_uppercase_g(format_t *str_struct);
void flag_uppercase_n(format_t *str_struct);
void flag_uppercase_s(format_t *str_struct);
void flag_uppercase_x(format_t *str_struct);
/**
 * @brief Get the sign attributes
 * @param format The format structure
 * @param nb The number to check
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void update_sign_attributes(format_t *str_struct, long double nb);

/**
 * @brief Get the width string depending on attributes
 * @param str_struct The format structure
 * @param str_list The string list
 * @param len The length of the string list
 * @return <b>char*</b> The width string
 * @author Nicolas TORO
 */
char *get_width(format_t *str_struct, char **str_list, size_t len);

/**
 * @brief Get the precision string
 * @param str_struct The format structure
 * @param nbr_str The number string
 * @return <b>char*</b> The precision string
 * @author Nicolas TORO
 */
char *get_precision(format_t *str_struct, char *nbr_str);



    /* String functions */

/**
* @brief Counts the number of times a letter (c) is in a string (str)
* @param str The string to check
* @param c The letter to count
* @return <b>int</b> The number of times the letter is in the string
* @author Nicolas TORO
*/
size_t my_count_letter(char const *str, char c);

/**
 * @brief The function that creates a string with the given format and args
 * @param format The string to format
 * @param args The list of args to insert in the string
 * @return <b>char*</b> The formatted string
 * @author Nicolas TORO
 */
char *my_create_str_va(const char *format, va_list args);

/**
 * @brief The function that creates a string with the given format and args
 * @param format The string to format
 * @param ... The list of args to insert in the string
 * @return <b>char*</b> The formatted string
 * @author Nicolas TORO
 */
char *my_create_str(const char *format, ...);

/**
 * @brief Gets the local time
 * @return <b>char *</b> The local time as a string
 * @author Nicolas TORO
 */
char *my_get_local_time(void);

/**
 * @brief Reverses the characters in a string (str)
 * and returns the string (str)
 * @param str The string to reverse
 * @return <b>char*</b> The reversed string
 * @author Nicolas TORO
 */
char *my_revstr(char *str);

/**
 * @brief Checks if a string (str) contains a character
 * in a list of characters (char_list)
 * @param str The string to check
 * @param char_list The list of characters to check
 * @return <b>bool</b> <u>true</u> if the string contains
 * a character in the list, <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_contains(char *str, char *char_list);

/**
 * @brief Checks if a string (str) is composed of characters
 * in the characters list (char_list) or 0 if not
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is composed of characters
 * in the characters list (char_list), <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is(char *str, const char *char_list);

/**
 * @brief Checks if a string (str) is alphabetical
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is alphabetical,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_alpha(char const *str);

/**
 * @brief Checks if a string (str) is lowercase
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is lowercase,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_lower(char const *str);

/**
 * @brief Checks if a string (str) is a number
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is a number,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_num(char const *str);

/**
 * @brief Checks if a string (str) is printable
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is printable,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_printable(char const *str);

/**
 * @brief Checks if a string (str) is uppercase
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is uppercase,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_upper(char const *str);

/**
 * @brief Capitalizes the first letter of each word in a string (str)
 * and lowercase the other letters
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strcapitalize(char *str);

/**
 * @brief Concatenates two strings (dest) and (src)
 * @note The destination string must be allocated and have enough space
 * @param dest The destination string
 * @param src The source string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strcat(char *dest, char const *src);

/**
 * @brief Compares two strings (s1) and (s2)
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @return <b>int</b> <u>0</u> if the strings are identical, otherwise
 * the difference between the first different characters in the strings
 * @author Nicolas TORO
 */
int my_strcmp(char const *s1, char const *s2);

/**
 * @brief Copies a string (src) and paste it on another string (dest)
 * @note The destination string must be allocated
 * @param dest The destination string
 * @param src The source string
 * @param n The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strcpy(char *dest, char const *src);

/**
 * @brief Duplicates a string (src) and returns the new string
 * @param src The string to duplicate
 * @return <b>char*</b> The duplicated string
 * @author Nicolas TORO
 */
char *my_strdup(char const *src);

/**
 * @brief Duplicates a word array (array) and returns the new array
 * @param array The word array to duplicate
 * @return <b>char**</b> The duplicated word array
 * @author Nicolas TORO
 */
char **my_strdup_word_array(char **array);

/**
 * @brief Returns the error message of the error number (error)
 * @param error The error number (errno)
 * @return <b>char**</b> The error message of the error number
 * @author Nicolas TORO
 */
const char *my_strerror(int error);

/**
 * @brief Returns the length of a string (str)
 * @param str The string to check
 * @return <b>size_t</b> The length of the string
 * @author Nicolas TORO
 */
size_t my_strlen(char const *str);

/**
 * @brief Replaces upcase by lowcase of a string (str)
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strlowcase(char *str);

/**
 * @brief Concatenates two strings (dest) and (src) with a defined size (nb)
 * @note The destination string must be allocated and have enough space
 * @param dest The destination string
 * @param src The source string
 * @param nb The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strncat(char *dest, char const *src, size_t n);

/**
 * @brief Compares two strings (s1) and (s2) with a defined size (n)
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The size of the strings to compare
 * @return <b>uint8_t</b> <u>0</u> if the strings are identical, otherwise
 * the difference between the first different characters in the strings
 * @author Nicolas TORO
 */
uint8_t my_strncmp(char const *s1, char const *s2, size_t n);

/**
 * @brief Copies a string (src) and paste it on another string (dest)
 * with a defined size (n)
 * @note The destination string must be allocated
 * @param dest The destination string
 * @param src The source string
 * @param n The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strncpy(char *dest, char const *src, size_t n);

/**
 * @brief Duplicates a string (src) with a defined size (n)
 * and returns the new string
 * @param src The string to duplicate
 * @param n The size of the string
 * @return <b>char*</b> The duplicated string
 * @author Nicolas TORO
 */
char *my_strndup(char const *src, size_t n);

/**
 * @brief Search a string (to_find) on another (str)
 * and returns the address of the first occurrence
 * @param str The string to be scanned
 * @param to_find The string to search in
 * @return <b>char*</b> The address of the <u>first occurrence</u>
 * of the string to_find in the string str, <u>NULL</u> otherwise
 * @author Nicolas TORO
 */
char *my_strstr(char *str, char const *to_find);

/**
 * @brief Replaces lowcase by upcase of a string (str)
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strupcase(char *str);

/**
 * @brief Returns the length of a wide string (wcs)
 * @param wcs The wide string to check
 * @return <b>size_t</b> The length of the wide string
 * @author Nicolas TORO
 */
size_t my_wcslen(const wchar_t *wcs);

/**
 * @brief Converts a wide-character string to a multibyte string
 * @param dest The destination string
 * @param src The source string
 * @param n The number of bytes to convert
 * @return <b>ssize_t</b> The number of bytes converted if successful,
 * the length of the string if dest is NULL, -1 if an error occured
 */
ssize_t my_wcstombs(char *dest, const wchar_t *src, size_t n);



    /* Write functions */

/**
 * @brief Print a formatted string to a file descriptor
 * @param fd The file descriptor
 * @param format The format string
 * @param ... The arguments to replace in the format string
 * @return <b>intmax_t</b> The length of the string
 * @author Nicolas TORO
 */
intmax_t my_dprintf(int fd, char const *format, ...);

/**
 * @brief Display a logs message
 * @param point The point in the code where the logs are displayed
 * @param type The type of logs message
 * @param message The message to display
 */
void my_logs_message(point_t point, logs_type_t type, const char *message);

/**
 * @brief Display a  point in the code
 * @note This function use the temporary malloc state
 * @param point The point in the code where the logs are displayed
 * @author Nicolas TORO
 */
void my_point(point_t point);

/**
 * @brief Print a formatted string
 * @param format The format string
 * @param ... The arguments to replace in the format string
 * @return <b>intmax_t</b> The length of the string
 * @author Nicolas TORO
 */
intmax_t my_printf(char const *format, ...);

/**
 * @brief Prints a char (c) in the stdout
 * @param c The char to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putchar(char c);

/**
 * @brief Prints a number (nb) in stdout
 * @param nb The number to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putnbr(intmax_t nb);

/**
 * @brief Prints a number (nb) in the requested base (base) in stdout
 * @param nbr The number to print
 * @param base The base to use
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putnbr_base(intmax_t nbr, char const *base);

/**
 * @brief Writes a string (str) in stdout
 * and returns the length of the printed string
 * @param str The string to print
 * @return <b>size_t</b> The length of the printed string
 * @author Nicolas TORO
 */
size_t my_putstr(char const *str);

/**
 * @brief Prints a string (str) in stderr and returns 84
 * @param str The string to print
 * @return <b>size_t</b> <u>84</u>
 * @author Nicolas TORO
 */
size_t my_putstr_error(char const *str);

/**
 * @brief Writes a string (str) in a file descriptor (fd)
 * and returns the length of the printed string
 * @param str The string to print
 * @param fd The file descriptor to write in
 * @return <b>size_t</b> The number of printed characters
 * @author Nicolas TORO
 */
size_t my_putstr_fd(char const *str, int fd);

/**
 * @brief Writes a string (str) in a file descriptor (fd), free it
 * and returns the length of the printed string
 * @param str The string to print
 * @param fd The file descriptor to write in
 * @return <b>size_t</b> The number of printed characters
 * @author Nicolas TORO
 */
size_t my_putstr_fd_free(char *str, int fd);

/**
 * @brief Prints a string (str) in stdout with a defined size (size)
 * and returns the length of the printed string
 * @param str The string to print
 * @param size The size of the string
 * @return <b>size_t</b> The length of the printed string
 * @author Nicolas TORO
 */
size_t my_putstr_sized(char const *str, size_t size);

/**
 * @brief Displays the linked list
 * @param list The linked list to display
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_show_list(node_t *list);

/**
 * @brief Prints the information of a parameter array (par)
 * @param par The information of the parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_show_param_array(info_param_t const *par);

/**
 * @brief Prints all word in an array (tab)
 * @param tab The array of words to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_show_word_array(char *const *tab);

/**
 * @brief Prints a memory dump of a string (str) with a defined size
 * @param str The string to print
 * @param size The size of the string
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_showmem(char const *str, size_t size);

/**
 * @brief Prints a string (str) but replaces
 * non-printable characters with their hexadecimal number
 * @param str The string to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_showstr(char const *str);

/**
 * @brief The debug mode variable
 * @note NONE (-2) and DEFAULT (-1): Returns just the value |
 * FALSE (0): Debug mode disable | TRUE (1): Debug mode enable
 * @param set The debug mode state
 * @return <b>my_bool_t</b> The debug mode state
 * @author Nicolas TORO
 */
my_bool_t debug_mode(my_bool_t set);

/**
 * @brief Updates the debug mode
 * @param type The new debug mode state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_debug_mode(my_bool_t type);

/**
 * @brief The extra logs variable
 * @note NONE (-2) and DEFAULT (-1): Returns just the value |
 * FALSE (0): Extra logs disable | TRUE (1): Extra logs enable
 * @param set The extra logs state
 * @return <b>my_bool_t</b> The extra logs state
 * @author Nicolas TORO
 */
my_bool_t extra_logs(my_bool_t set);

/**
 * @brief Updates the extra logs state
 * @param type The new extra logs state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_extra_logs(my_bool_t type);

#endif /* FUNCTIONS_H_ */
