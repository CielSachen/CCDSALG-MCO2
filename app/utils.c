/*
 * Social Network uses graphs to represent relationships between users.
 * Copyright (C) 2025  Raphael Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file utils.c
 * @brief The source code containing the implementation of the IO utility functions.
 * @author Raphael Panaligan
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
