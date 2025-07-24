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

#ifndef SOCIAL_NETWORK_QUEUE_H_
#define SOCIAL_NETWORK_QUEUE_H_

#include <stddef.h>

#include "graph.h"

typedef struct Queue {
    Vertex data[MAX_GRAPH_VERTEX_COUNT];
    size_t front;
    size_t rear;
} Queue;

void initialize_queue(Queue *const queue);

void enqueue(Queue *const queue, const Vertex element);

void dequeue(Queue *const queue);

void peak(Queue *const queue, Vertex elm);

bool is_full(const Queue *const queue);

bool is_empty(const Queue *const queue);

#endif  // SOCIAL_NETWORK_QUEUE_H_
