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
 * @file queue.c
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#include "social_network/queue.h"

#include <string.h>

/**
 * @brief Initializes a queue’s data and indexes to their default values.
 * @param[in,out] queue The queue to initialize.
 */
void initialize_queue(Queue *const queue) {
    queue->front = 0;
    queue->rear = 0;

    for (size_t i = 0; i < MAX_QUEUE_LENGTH; i++) {
        for (size_t j = 0; j < MAX_VERTEX_LABEL_LENGTH; j++) {
            queue->data[i][j] = '\0';
        }
    }
}

/**
 * @brief Adds an element to the rear of the queue.
 * @param[in,out] queue The queue to add to.
 * @param[in] elm The element to add.
 * @pre The queue is not full.
 */
void enqueue(Queue *const queue, const Vertex elm) { strncpy(queue->data[queue->rear++], elm, MAX_GRAPH_VERTEX_COUNT); }

/**
 * @brief Removes the element at the front of the queue.
 * @param[in,out] queue The queue to remove from.
 * @pre The queue is not empty.
 */
void dequeue(Queue *const queue) { queue->front++; }

/**
 * @brief Gets the element at the front of the queue.
 * @param[in] queue The queue to get from.
 * @param[out] elm The element at the front of the queue.
 * @pre The queue is not empty.
 */
void peak(Queue *const queue, Vertex elm) { strncpy(elm, queue->data[queue->front], MAX_VERTEX_LABEL_LENGTH); }

/**
 * @brief Checks if a queue contains the maximum number of elements.
 * @param[in] queue The queue to check.
 * @return Whether the queue's rear index is `MAX_STACK_LENGTH`.
 */
bool is_full(const Queue *const queue) { return queue->rear == MAX_GRAPH_VERTEX_COUNT; }

/**
 * @brief Checks if a queue contains contains no queueing elements.
 * @param[in] queue The queue to check.
 * @return Whether the queue’s front and rear indexes are equal.
 */
bool is_empty(const Queue *const queue) { return queue->front == queue->rear; }
