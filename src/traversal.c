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

#include "social_network/traversal.h"

#include <string.h>

#include "queue.c"

void breadth_first_search(const Graph *const graph, const Vertex starting_vertex,
                          Vertex traversed_vertices[MAX_GRAPH_VERTEX_COUNT], size_t *const traversed_vertex_cnt) {
    *traversed_vertex_cnt = 0;

    bool is_visited[graph->vertex_count];

    for (size_t i = 0; i < graph->vertex_count; i++) {
        is_visited[i] = false;
    }

    Queue queue;

    initialize_queue(&queue);

    is_visited[get_vertex_index(graph, starting_vertex)] = true;

    enqueue(&queue, starting_vertex);

    while (!is_empty(&queue)) {
        peak(&queue, traversed_vertices[*traversed_vertex_cnt]);
        dequeue(&queue);

        *traversed_vertex_cnt += 1;

        size_t curr_vertex_idx = get_vertex_index(graph, traversed_vertices[*traversed_vertex_cnt - 1]);
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
