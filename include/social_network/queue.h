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
 * @file queue.h
 * @brief The header containing the public APIs of the queue implementation and its helper functions.
 * @author Raphael Panaligan
 * @copyright GNU AGPLv3
 */

#ifndef SOCIAL_NETWORK_QUEUE_H_
#define SOCIAL_NETWORK_QUEUE_H_

#include <stddef.h>

#include "graph.h"

/**
 * @brief A collection implementing the [queue data structure](https://www.geeksforgeeks.org/dsa/queue-data-structure/)
 * using an array.
 * @details This is a simple implementation, not a circular implementation. Therefore, the queue can only be consumed
 * once.
 */
typedef struct Queue {
    /** @brief The ordered data contained in the queue. */
    Vertex data[MAX_GRAPH_VERTEX_COUNT];
    /** @brief The index of the first element in the queue. */
    size_t front;
    /** @brief The index of the last element in the queue. */
    size_t rear;
} Queue;

/**
 * @brief Initializes a queue’s data and indexes to their default values.
 * @param[in,out] queue The queue to initialize.
 */
void initialize_queue(Queue *const queue);

/**
 * @brief Adds an element to the rear of the queue.
 * @param[in,out] queue The queue to add to.
 * @param[in] element The element to add.
 */
void enqueue(Queue *const queue, const Vertex element);

/**
 * @brief Removes the element at the front of the queue.
 * @param[in,out] queue The queue to remove from.
 */
void dequeue(Queue *const queue);

/**
 * @brief Gets the element at the front of the queue.
 * @param[in] queue The queue to get from.
 * @param[out] element The element at the front of the queue.
 */
void peak(Queue *const queue, Vertex element);

/**
 * @brief Checks if a queue contains the maximum number of elements.
 * @param[in] queue The queue to check.
 * @return Whether the queue's rear index is `MAX_STACK_LENGTH`.
 */
bool is_full(const Queue *const queue);

/**
 * @brief Checks if a queue contains contains no queueing elements.
 * @param[in] queue The queue to check.
 * @return Whether the queue’s front and rear indexes are equal.
 */
bool is_empty(const Queue *const queue);

#endif  // SOCIAL_NETWORK_QUEUE_H_
