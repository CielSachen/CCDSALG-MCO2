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
 * @file graph.c
 * @brief The source code containing the implementation of the graph helper functions.
 * @author Raphael Panaligan
 * @copyright GNU AGPLv3
 */

#include "social_network/graph.h"

#include <string.h>

/**
 * @brief Initializes a graph’s vertex adjacency arrays to their default values and sets its vertex count.
 * @param[in,out] graph The graph to initialize.
 * @param vertex_count The number of vertices the graph should contain.
 * @pre The @p vertex_count doesn’t exceed `MAX_GRAPH_VERTEX_COUNT`.
 */
void initialize_graph(Graph *const graph, const size_t vertex_cnt) {
    graph->vertex_count = vertex_cnt;
    graph->adjacencies_length = 0;

    for (size_t vertex_idx = 0; vertex_idx < MAX_GRAPH_VERTEX_COUNT; vertex_idx++) {
        for (size_t adjacency_idx = 0; adjacency_idx < MAX_GRAPH_VERTEX_COUNT; adjacency_idx++) {
            for (size_t i = 0; i < MAX_VERTEX_LABEL_LENGTH; i++) {
                graph->adjacencies_by_vertex[vertex_idx][adjacency_idx][i] = '\0';
            }
        }
    }
}

/**
 * @brief Clones the contents of a graph into another, presumably uninitialized, graph.
 * @param[in] graph The graph to clone from.
 * @param[out] new_graph The graph to clone to.
 */
void clone_graph(const Graph *const graph, Graph *const new_graph) {
    initialize_graph(new_graph, graph->vertex_count);

    for (size_t i = 0; i < new_graph->vertex_count; i++) {
        size_t j = 1;

        if (strlen(graph->adjacencies_by_vertex[i][j]) == 0) {
            add_adjacency(new_graph, graph->adjacencies_by_vertex[i][0], NULL);

            continue;
        }

        while (strlen(graph->adjacencies_by_vertex[i][j]) > 0) {
            add_adjacency(new_graph, graph->adjacencies_by_vertex[i][0], graph->adjacencies_by_vertex[i][j]);

            j++;
        }
    }
}

/**
 * @brief Gets the index of the adjacency array of a vertex from a graph, if the graph contains the vertex.
 * @param[in] graph The graph to get from.
 * @param[in] vertex The vertex to get the index of.
 * @return The index of the vertex’ adjacency array, or `MAX_GRAPH_VERTEX_COUNT` if the graph doesn’t contain the
 * vertex.
 */
size_t get_vertex_index(const Graph *const graph, const Vertex vertex) {
    for (size_t i = 0; i < graph->adjacencies_length; i++) {
        if (strncmp(graph->adjacencies_by_vertex[i][0], vertex, MAX_VERTEX_LABEL_LENGTH) == 0) {
            return i;
        }
    }

    return MAX_GRAPH_VERTEX_COUNT;
}

/**
 * @brief Checks if a graph contains a vertex.
 * @param[in] graph The graph to check.
 * @param[in] vertex The vertex to check for.
 * @return Whether the graph contains the vertex.
 */
bool has_vertex(const Graph *const graph, const Vertex vertex) {
    return get_vertex_index(graph, vertex) != MAX_GRAPH_VERTEX_COUNT;
}

/**
 * @brief Adds an adjacency between a pair of vertices to a graph.
 * @details This adds the adjacent vertex to the array of the key vertex. If the array doesn’t exist, this creates the
 * array before adding the adjacent vertex. If an adjacent vertex is not supplied, then this will still create the array
 * for the key vertex if it doesn’t exist.
 * @param[in,out] graph The graph to add to.
 * @param[in] key_vertex The key vertex of the adjacency.
 * @param[in] adjacent_vertex The vertex adjacent to the key vertex.
 * @pre The graph’s vertex count has been checked against and the number of vertices will not exceed
 * `MAX_GRAPH_VERTEX_COUNT`.
 */
void add_adjacency(Graph *const graph, const Vertex key_vertex, const Vertex adjacent_vertex) {
    const bool has_key_vertex = has_vertex(graph, key_vertex);

    const size_t key_vertex_idx =
        has_key_vertex ? get_vertex_index(graph, adjacent_vertex) : graph->adjacencies_length++;

    if (!has_key_vertex) {
        strncpy(graph->adjacencies_by_vertex[key_vertex_idx][0], key_vertex, MAX_VERTEX_LABEL_LENGTH);
    }

    if (!adjacent_vertex) {
        return;
    }

    size_t adjacent_vertex_idx = 1;

    while (strlen(graph->adjacencies_by_vertex[key_vertex_idx][adjacent_vertex_idx]) > 0) {
        adjacent_vertex_idx++;
    }

    strncpy(graph->adjacencies_by_vertex[key_vertex_idx][adjacent_vertex_idx], adjacent_vertex,
            MAX_VERTEX_LABEL_LENGTH);
}

/**
 * @brief Gets the total number of adjacencies in a key led array of adjacencies.
 * @param[in] adjacencies The key led adjacencies to get from.
 * @return The total number of adjacencies in the key led array of adjacencies.
 */
size_t get_adjacency_count(const Vertex adjacencies[MAX_GRAPH_VERTEX_COUNT]) {
    size_t adjacency_cnt = 0;

    while (strlen(adjacencies[adjacency_cnt + 1]) > 0) {
        adjacency_cnt++;
    }

    return adjacency_cnt;
}

/**
 * @brief Checks if a key led array of adjacencies contains an adjacent vertex.
 * @param[in] adjacencies The key led adjacencies to check against.
 * @param[in] adjacent_vertex The adjacent vertex to check for.
 * @return Whether the key led array of adjacencies contains the adjacent vertex.
 */
bool has_adjacency(const Vertex adjacencies[MAX_GRAPH_VERTEX_COUNT], const Vertex adjacent_vertex) {
    size_t adjacency_cnt = 1;

    while (strlen(adjacencies[adjacency_cnt]) > 0) {
        if (strncmp(adjacencies[adjacency_cnt], adjacent_vertex, MAX_VERTEX_LABEL_LENGTH) == 0) {
            return true;
        }

        adjacency_cnt++;
    }

    return false;
}

/**
 * @brief Sorts the adjacency arrays by their keys alphabetically, and sorts their adjacent vertices alphabetically.
 * @param[in,out] graph The graph to sort.
 */
void sort_adjacencies(Graph *const graph) {
    for (size_t i = 0; i < graph->vertex_count; i++) {
        for (size_t j = 0; j < graph->vertex_count - 1; j++) {
            if (strncmp(graph->adjacencies_by_vertex[j][0], graph->adjacencies_by_vertex[j + 1][0],
                        MAX_VERTEX_LABEL_LENGTH) > 0) {
                for (size_t k = 0; k < MAX_GRAPH_VERTEX_COUNT; k++) {
                    Vertex temp;

                    strncpy(temp, graph->adjacencies_by_vertex[j][k], MAX_VERTEX_LABEL_LENGTH);
                    strncpy(graph->adjacencies_by_vertex[j][k], graph->adjacencies_by_vertex[j + 1][k],
                            MAX_VERTEX_LABEL_LENGTH);
                    strncpy(graph->adjacencies_by_vertex[j + 1][k], temp, MAX_VERTEX_LABEL_LENGTH);
                }
            }
        }
    }

    for (size_t i = 0; i < graph->vertex_count; i++) {
        for (size_t j = 0; j < graph->vertex_count; j++) {
            size_t k = 1;

            while (strlen(graph->adjacencies_by_vertex[i][k + 1]) > 0) {
                if (strncmp(graph->adjacencies_by_vertex[i][k], graph->adjacencies_by_vertex[i][k + 1],
                            MAX_VERTEX_LABEL_LENGTH) > 0) {
                    Vertex temp;

                    strncpy(temp, graph->adjacencies_by_vertex[i][k], MAX_VERTEX_LABEL_LENGTH);
                    strncpy(graph->adjacencies_by_vertex[i][k], graph->adjacencies_by_vertex[i][k + 1],
                            MAX_VERTEX_LABEL_LENGTH);
                    strncpy(graph->adjacencies_by_vertex[i][k + 1], temp, MAX_VERTEX_LABEL_LENGTH);
                }

                k++;
            }
        }
    }
}

/**
 * @brief Gets the edges formed by connections between vertices contained in a graph.
 * @param[in] graph The graph to get from.
 * @param[out] edges The edges of the graph.
 * @param[out] edge_count The number of edges the graph has.
 */
void get_edges(const Graph *const graph, GraphEdge edges[], size_t *const edge_cnt) {
    *edge_cnt = 0;

    for (size_t i = 0; i < graph->vertex_count; i++) {
        size_t j = 1;

        while (strlen(graph->adjacencies_by_vertex[i][j]) > 0) {
            if (!has_edge(edges, *edge_cnt, graph->adjacencies_by_vertex[i][0], graph->adjacencies_by_vertex[i][j])) {
                GraphEdge *edge = &edges[*edge_cnt];

                strncpy(edge->source, graph->adjacencies_by_vertex[i][0], MAX_VERTEX_LABEL_LENGTH);
                strncpy(edge->destination, graph->adjacencies_by_vertex[i][j], MAX_VERTEX_LABEL_LENGTH);

                *edge_cnt += 1;
            }

            j++;
        }
    }
}

/**
 * @brief Checks if a pair of vertices already has a corresponding edge in an array of edges.
 * @param[in] edges The edges to check against.
 * @param[in] edge_cnt The number of edges to check against.
 * @param[in] source_vertex The first or source vertex to check for.
 * @param[in] destination_vertex The second or destination vertex to check for.
 * @return Whether the pair of vertices has a corresponding edge in the array of edges.
 */
bool has_edge(const GraphEdge edges[], const size_t edge_cnt, const Vertex src_vertex, const Vertex dest_vertex) {
    for (size_t i = 0; i < edge_cnt; i++) {
        const GraphEdge *const edge = &edges[i];

        if ((strncmp(edge->source, src_vertex, MAX_VERTEX_LABEL_LENGTH) == 0 &&
             strncmp(edge->destination, dest_vertex, MAX_VERTEX_LABEL_LENGTH) == 0) ||
            (strncmp(edge->source, dest_vertex, MAX_VERTEX_LABEL_LENGTH) == 0 &&
             strncmp(edge->destination, src_vertex, MAX_VERTEX_LABEL_LENGTH) == 0)) {
            return true;
        }
    }

    return false;
}
