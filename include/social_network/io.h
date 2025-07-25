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

#ifndef SOCIAL_NETWORK_IO_H_
#define SOCIAL_NETWORK_IO_H_

#include <stdbool.h>

#include "graph.h"

#define BUFFER_SIZE 32

#define WHITESPACE_DELIMITER " \f\n\r\t\v"

#define NULL_VERTEX_LABEL "-1"

typedef char StringBuffer[BUFFER_SIZE + 1];

bool parse_graph_from_file(const StringBuffer input_file_name, Graph *const graph);

void create_output_file_1(const Graph *const graph, const char graph_name);

void create_output_file_2(const Graph *const graph, const char graph_name);

void create_output_file_3(const Graph *const graph, const char graph_name);

void create_output_file_4(const Graph *const graph, const char graph_name);

void create_output_file_5(const Graph *const graph, const char graph_name, const Vertex starting_vertex);

void create_output_file_6(const Graph *const graph, const char graph_name, const Vertex starting_vertex);

void create_output_file_7(const Graph *const graph, const char graph_name, const Graph *const subgraph,
                          const char subgraph_name);

#endif  // SOCIAL_NETWORK_IO_H_
