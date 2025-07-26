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
 * @file io.h
 * @brief The helper functions that are used to parse graphs from input files and to create output files.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOCIAL_NETWORK_IO_H_
#define SOCIAL_NETWORK_IO_H_

#include <stdbool.h>

#include "graph.h"

/** @brief The size of buffers used in IO operations. */
#define BUFFER_SIZE 32

/** @brief The delimiter to use when tokenizing strings to exclude whitespace characters. */
#define WHITESPACE_DELIMITER " \f\n\r\t\v"

/** @brief The vertex label used to represent NULL, or the end of the list. */
#define NULL_VERTEX_LABEL "-1"

/** @brief A string used to store text read from an input stream. */
typedef char StringBuffer[BUFFER_SIZE + 1];

/**
 * @brief Parses a graph represented with an adjacency list from an input file.
 * @param[in] input_file_name The name of the input file, or the path to it.
 * @param[out] graph The graph parsed from the input file.
 * @return Whether the input file was opened and read by the program.
 */
bool parse_graph_from_file(const StringBuffer input_file_name, Graph *const graph);

/**
 * @brief Creates the first output file, containing a graph’s vertex labels and edges.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 */
void create_output_file_1(const Graph *const graph, const char graph_name);

/**
 * @brief Creates the second output file, containing the degrees of a graph’s vertices.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 */
void create_output_file_2(const Graph *const graph, const char graph_name);

/**
 * @brief Creates the third output file, containing the adjacency list representation of a graph.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 */
void create_output_file_3(const Graph *const graph, const char graph_name);

/**
 * @brief Creates the fourth output file, containing the adjacency matrix representation of a graph.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 */
void create_output_file_4(const Graph *const graph, const char graph_name);

/**
 * @brief Creates the fifth output file, containing the non-repeating traversal sequence of a graph using breadth-first
 * search.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 */
void create_output_file_5(const Graph *const graph, const char graph_name, const Vertex starting_vertex);

/**
 * @brief Creates the sixth output file, containing the non-repeating traversal sequence of a graph using depth-first
 * search.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] starting_vertex The vertex to start the traversal from.
 */
void create_output_file_6(const Graph *const graph, const char graph_name, const Vertex starting_vertex);

/**
 * @brief Creates the seventh output file, containing the step-by-step check of whether a graph is a subgraph of
 * another.
 * @param[in] graph The graph to use.
 * @param[in] graph_name The name of the graph to use.
 * @param[in] subgraph The subgraph to use.
 * @param[in] subgraph_name The name of the subgraph to use.
 */
void create_output_file_7(const Graph *const graph, const char graph_name, const Graph *const subgraph,
                          const char subgraph_name);

#endif  // SOCIAL_NETWORK_IO_H_

#ifdef __cplusplus
}
#endif
