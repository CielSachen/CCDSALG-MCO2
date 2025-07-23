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

#include "social_network/queue.h"

#include <stdio.h>
#include <string.h>

void initialize_queue(Queue *const queue) {
    queue->front = 0;
    queue->rear = 0;

    for (size_t i = 0; i < MAX_GRAPH_VERTEX_COUNT; i++) {
        for (size_t j = 0; j < MAX_VERTEX_LABEL_LENGTH; j++) {
            queue->data[i][j] = '\0';
        }
    }
}

void enqueue(Queue *const queue, const Vertex elm) { strncpy(queue->data[queue->rear++], elm, MAX_GRAPH_VERTEX_COUNT); }

void dequeue(Queue *const queue) { queue->front++; }

void peak(Queue *const queue, Vertex elm) { strncpy(elm, queue->data[queue->front], MAX_VERTEX_LABEL_LENGTH); }

bool is_full(const Queue *const queue) { return queue->rear == MAX_GRAPH_VERTEX_COUNT; }

bool is_empty(const Queue *const queue) { return queue->front == queue->rear; }
