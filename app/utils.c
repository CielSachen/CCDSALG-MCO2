/**
 * @file utils.c
 * @brief The source code containing the implementation of the IO utility functions.
 * @copyright GNU AGPLv3
 */

#include "utils.h"

#include <stdio.h>
#include <string.h>

/** @brief Clears the input buffer of all characters awaiting scanning. */
void clear_input_buffer(void) {
    int excess_char;

    while ((excess_char = getchar()) != '\n' && excess_char != EOF);
}

/**
 * @brief Gets a string typed input from the user.
 * @param[out] str The input received from the user.
 * @param max_len The maximum length of the output string.
 */
void get_string_input(char str[], const size_t max_len) {
    fflush(stdout);

    fgets(str, max_len, stdin);

    const size_t last_idx = strlen(str) - 1;

    if (str[last_idx] == '\n') {
        str[last_idx] = '\0';
    } else {
        clear_input_buffer();
    }
}
