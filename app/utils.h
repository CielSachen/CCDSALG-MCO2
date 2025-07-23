/*
 * Social Network uses graphs to represent relationships between users.
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
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
