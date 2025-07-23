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

#ifndef SOCIAL_NETWORK_GRAPH_H_
#define SOCIAL_NETWORK_GRAPH_H_

#include <stdbool.h>
#include <stddef.h>

#define MAX_VERTEX_LABEL_LENGTH 8

#define MAX_GRAPH_VERTEX_COUNT 20

typedef char Vertex[MAX_VERTEX_LABEL_LENGTH + 1];

typedef struct Graph {
    const size_t vertex_count;
    Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT][MAX_GRAPH_VERTEX_COUNT];
    size_t adjacencies_length;
} Graph;

typedef struct GraphEdge {
    Vertex source;
    Vertex destination;
} GraphEdge;

void initialize_graph(Graph *const graph, const size_t vertex_count);

size_t get_vertex_index(const Graph *const graph, const Vertex vertex);

bool has_vertex(const Graph *const graph, const Vertex vertex);

void add_edge(Graph *const graph, const Vertex source_vertex, const Vertex destination_vertex);

void get_edges(const Graph *const graph, GraphEdge edges[], size_t *const edge_count);

void clone_graph(const Graph *const graph, Graph *const new_graph);

void sort_adjacencies(Graph *const graph);

size_t get_adjacency_count(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT]);

bool has_adjacency(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT], const Vertex vertex);

#endif  // SOCIAL_NETWORK_GRAPH_H_
