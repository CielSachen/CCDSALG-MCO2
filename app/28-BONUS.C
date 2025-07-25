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
 * @file 28-BONUS.c
 * @brief The source code containing the implementation of the bonus social network graphing program.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#include <stdio.h>
#include <string.h>

#include "social_network/io.h"
#include "utils.h"

/**
 * @brief The entry point of the bonus social network graphing program.
 * @return The program’s resulting exit code.
 */
int main(void) {
    StringBuffer in_file_name;

    printf("Input filename (Parent graph): ");

    get_string_input(in_file_name, sizeof in_file_name);

    Graph graph;
    const char graph_name = in_file_name[strlen(in_file_name) - 5];

    if (!parse_graph_from_file(in_file_name, &graph)) {
        // Prior function prints an error message.
        return 1;
    }

    sort_adjacencies(&graph);

    printf("Input filename (Subgraph): ");

    get_string_input(in_file_name, sizeof in_file_name);

    Graph subgraph;
    const char subgraph_name = in_file_name[strlen(in_file_name) - 5];

    if (!parse_graph_from_file(in_file_name, &subgraph)) {
        // Prior function prints an error message.
        return 1;
    }

    sort_adjacencies(&subgraph);

    create_output_file_7(&graph, graph_name, &subgraph, subgraph_name);

    return 0;
}
