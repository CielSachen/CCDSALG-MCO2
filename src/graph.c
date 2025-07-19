#include "social_network/graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node *create_node(const Vertex vertex) {
    Node *node = malloc(sizeof(Node));

    if (!node) {
        return NULL;
    }

    strncpy(node->vertex, vertex, MAX_VERTEX_LABEL_LENGTH);

    node->next = NULL;

    return node;
}

Graph *create_graph(const size_t vertex_cnt) {
    Graph *graph = malloc(sizeof(Graph));

    if (!graph) {
        return NULL;
    }

    *(size_t *)&graph->vertex_count = vertex_cnt;
    graph->adjacencies = malloc(vertex_cnt * sizeof(Node *));

    for (size_t i = 0; i < vertex_cnt; i++) {
        graph->adjacencies[i] = NULL;
    }

    graph->adjacencies_length = 0;

    return graph;
}

static size_t get_vertex_index(const Graph *const graph, const Vertex vertex) {
    for (size_t i = 0; i < graph->vertex_count; i++) {
        Node *curr_node = graph->adjacencies[i];

        if (!curr_node) {
            break;
        }

        if (strncmp(curr_node->vertex, vertex, MAX_VERTEX_LABEL_LENGTH) == 0) {
            return i;
        }
    }

    return SIZE_MAX;
}

bool has_vertex(const Graph *const graph, const Vertex vertex) { return get_vertex_index(graph, vertex) != SIZE_MAX; }

bool add_edge(Graph *const graph, const Vertex src_vertex, const Vertex dest_vertex) {
    const size_t src_adjacency_idx =
        has_vertex(graph, src_vertex) ? get_vertex_index(graph, src_vertex) : graph->adjacencies_length++;
    Node *src_list = graph->adjacencies[src_adjacency_idx];

    if (!src_list) {
        Node *src_node = create_node(src_vertex);

        if (!src_node) {
            return false;
        }

        graph->adjacencies[src_adjacency_idx] = src_list = src_node;
    }

    if (!dest_vertex) {
        return true;
    }

    Node *curr_node = src_list;

    while (curr_node->next) {
        curr_node = curr_node->next;
    }

    Node *dest_node = create_node(dest_vertex);

    if (!dest_node) {
        return false;
    }

    curr_node->next = dest_node;

    return true;
}
