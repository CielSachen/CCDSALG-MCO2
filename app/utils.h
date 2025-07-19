/**
 * @file utils.h
 * @brief The header containing the APIs of the IO utility functions.
 * @copyright GNU AGPLv3
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stddef.h>

/** @brief Clears the input buffer of all characters awaiting scanning. */
void clear_input_buffer(void);

/**
 * @brief Gets a string typed input from the user.
 * @param[out] string The input received from the user.
 * @param max_length The maximum length of the output string.
 */
void get_string_input(char string[], const size_t max_length);

#endif  // UTILS_H_
