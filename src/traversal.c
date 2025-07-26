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
 * @file traversal.c
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#include "social_network/traversal.h"

#include <string.h>

#include "social_network/queue.h"

/**
 * @brief Traverses through all of a graph’s connected vertices starting from a specific vertex.
 * @details This uses the breadth-first search algorithm to traverse through the graph.
 * @param[in] graph The graph to traverse through.
 * @param starting_vertex The vertex to start from.
 * @param[out] visited_vertices The vertices visited during the traversal.
 * @param[out] visited_vertex_cnt The number of vertices visited during the traversal.
 */
void breadth_first_search(const Graph *const graph, const Vertex starting_vertex,
                          Vertex visited_vertices[MAX_GRAPH_VERTEX_COUNT], size_t *const visited_vertex_cnt) {
    *visited_vertex_cnt = 0;

    bool is_visited[graph->vertex_count];

    for (size_t i = 0; i < graph->vertex_count; i++) {
        is_visited[i] = false;
    }

    Queue queue;

    initialize_queue(&queue);

    is_visited[get_vertex_index(graph, starting_vertex)] = true;

    enqueue(&queue, starting_vertex);

    while (!is_empty(&queue)) {
        peak(&queue, visited_vertices[*visited_vertex_cnt]);
        dequeue(&queue);

        *visited_vertex_cnt += 1;

        size_t curr_vertex_idx = get_vertex_index(graph, visited_vertices[*visited_vertex_cnt - 1]);
        size_t i = 1;

        while (strlen(graph->adjacencies_by_vertex[curr_vertex_idx][i]) > 0) {
            size_t adjacent_vertex_idx = get_vertex_index(graph, graph->adjacencies_by_vertex[curr_vertex_idx][i]);

            if (!is_visited[adjacent_vertex_idx]) {
                is_visited[adjacent_vertex_idx] = true;

                enqueue(&queue, graph->adjacencies_by_vertex[adjacent_vertex_idx][0]);
            }

            i++;
        }
    }

    return;
}

/**
 * @brief Traverses through all of a graph’s connected vertices starting from a specific vertex.
 * @details This uses the depth-first search algorithm to traverse through the graph.
 * @param[in] graph The graph to traverse through.
 * @param starting_vertex The vertex to start from.
 * @param[in,out] is_visited The visit statuses of the graph’s vertices.
 * @param[out] visited_vertices The vertices visited during the traversal.
 * @param[out] visited_vertex_cnt The number of vertices visited during the traversal.
 */
static void deep_depth_first_search(const Graph *const graph, const Vertex starting_vertex,
                                    bool is_visited[MAX_GRAPH_VERTEX_COUNT],
                                    Vertex visited_vertices[MAX_GRAPH_VERTEX_COUNT], size_t *const visited_vertex_cnt) {
    size_t starting_vertex_idx = get_vertex_index(graph, starting_vertex);

    strncpy(visited_vertices[*visited_vertex_cnt], starting_vertex, MAX_VERTEX_LABEL_LENGTH);

    *visited_vertex_cnt += 1;

    is_visited[starting_vertex_idx] = true;

    size_t i = 1;

    while (strlen(graph->adjacencies_by_vertex[starting_vertex_idx][i]) > 0) {
        size_t adjacent_vertex_idx = get_vertex_index(graph, graph->adjacencies_by_vertex[starting_vertex_idx][i]);

        if (!is_visited[adjacent_vertex_idx]) {
            is_visited[adjacent_vertex_idx] = true;

            deep_depth_first_search(graph, graph->adjacencies_by_vertex[adjacent_vertex_idx][0], is_visited,
                                    visited_vertices, visited_vertex_cnt);
        }

        i++;
    }
}

/**
 * @brief Traverses through all of a graph’s connected vertices starting from a specific vertex.
 * @details This uses the depth-first search algorithm to traverse through the graph.
 * @param[in] graph The graph to traverse through.
 * @param starting_vertex The vertex to start from.
 * @param[out] visited_vertices The vertices visited during the traversal.
 * @param[out] visited_vertex_cnt The number of vertices visited during the traversal.
 */
void depth_first_search(const Graph *const graph, const Vertex starting_vertex,
                        Vertex visited_vertices[MAX_GRAPH_VERTEX_COUNT], size_t *const visited_vertex_cnt) {
    *visited_vertex_cnt = 0;

    bool is_visited[graph->vertex_count];

    for (size_t i = 0; i < graph->vertex_count; i++) {
        is_visited[i] = false;
    }

    deep_depth_first_search(graph, starting_vertex, is_visited, visited_vertices, visited_vertex_cnt);
}
