#include "social_network/graph.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node *create_node(const Vertex vertex) {
    Node *const node = malloc(sizeof(Node));

    if (!node) {
        return NULL;
    }

    strncpy(node->vertex, vertex, MAX_VERTEX_LABEL_LENGTH);

    node->next = NULL;

    return node;
}

Graph *create_graph(const size_t vertex_cnt) {
    Graph *const graph = malloc(sizeof(Graph));

    if (!graph) {
        return NULL;
    }

    *(size_t *)&graph->vertex_count = vertex_cnt;
    graph->adjacencies = malloc(vertex_cnt * sizeof(Node *));

    if (!graph->adjacencies) {
        free(graph);

        return NULL;
    }

    for (size_t i = 0; i < vertex_cnt; i++) {
        graph->adjacencies[i] = NULL;
    }

    graph->adjacencies_length = 0;

    return graph;
}

static size_t get_vertex_index(const Graph *const graph, const Vertex vertex) {
    for (size_t i = 0; i < graph->vertex_count; i++) {
        const Node *const curr_node = graph->adjacencies[i];

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
    // False-Positive: Assigned value is at least NULL.
    Node *src_list = graph->adjacencies[src_adjacency_idx];  // NOLINT

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

    Node *const dest_node = create_node(dest_vertex);

    if (!dest_node) {
        return false;
    }

    curr_node->next = dest_node;

    return true;
}

static bool is_existing(GraphEdge *graph_edges[], const Vertex src_vertex, const Vertex dest_vertex) {
    for (size_t i = 0; graph_edges[i]; i++) {
        GraphEdge *graph_edge = graph_edges[i];

        if ((strncmp(graph_edge->source, src_vertex, MAX_VERTEX_LABEL_LENGTH) == 0 &&
             strncmp(graph_edge->destination, dest_vertex, MAX_VERTEX_LABEL_LENGTH) == 0) ||
            (strncmp(graph_edge->source, dest_vertex, MAX_VERTEX_LABEL_LENGTH) == 0 &&
             strncmp(graph_edge->destination, src_vertex, MAX_VERTEX_LABEL_LENGTH) == 0)) {
            return true;
        }
    }

    return false;
}

GraphEdge **get_edges(const Graph *const graph) {
    const size_t max_edge_cnt = powl(graph->vertex_count, 2);
    GraphEdge **edges = malloc(max_edge_cnt * sizeof(GraphEdge *));

    if (!edges) {
        return NULL;
    }

    for (size_t i = 0; i < max_edge_cnt; i++) {
        edges[i] = NULL;
    }

    size_t edge_cnt = 0;

    for (size_t i = 0; i < graph->vertex_count; i++) {
        const Node *curr_node = graph->adjacencies[i];

        Vertex vertex_label;

        strncpy(vertex_label, curr_node->vertex, MAX_VERTEX_LABEL_LENGTH);

        while (curr_node->next) {
            curr_node = curr_node->next;

            if (!is_existing(edges, vertex_label, curr_node->vertex)) {
                GraphEdge *edge = malloc(sizeof(GraphEdge));

                if (!edge) {
                    return NULL;
                }

                strncpy(edge->source, vertex_label, MAX_VERTEX_LABEL_LENGTH);
                strncpy(edge->destination, curr_node->vertex, MAX_VERTEX_LABEL_LENGTH);

                edges[edge_cnt++] = edge;
            }
        }
    }

    return edges;
}

Graph *clone_graph(const Graph *const graph) {
    Graph *const new_graph = create_graph(graph->vertex_count);

    if (!new_graph) {
        return NULL;
    }

    for (size_t i = 0; i < new_graph->vertex_count; i++) {
        const Node *curr_node = graph->adjacencies[i];

        Vertex vertex_label;

        strncpy(vertex_label, curr_node->vertex, MAX_VERTEX_LABEL_LENGTH);

        if (!curr_node->next) {
            if (!add_edge(new_graph, vertex_label, NULL)) {
                free(new_graph);

                return NULL;
            }

            continue;
        }

        while (curr_node->next) {
            curr_node = curr_node->next;

            if (!add_edge(new_graph, vertex_label, curr_node->vertex)) {
                free(new_graph);

                return NULL;
            }
        }
    }

    return new_graph;
}

void sort_graph_adjacencies(Graph *const graph) {
    for (size_t i = 0; i < graph->vertex_count; i++) {
        for (size_t j = 0; j < graph->vertex_count - 1; j++) {
            Node *curr_node = graph->adjacencies[j];
            Node *next_node = graph->adjacencies[j + 1];

            if (strncmp(curr_node->vertex, next_node->vertex, MAX_VERTEX_LABEL_LENGTH) > 0) {
                Node *temp = curr_node;
                graph->adjacencies[j] = graph->adjacencies[j + 1];
                graph->adjacencies[j + 1] = temp;
            }
        }
    }

    for (size_t i = 0; i < graph->vertex_count; i++) {
        Node *const node = graph->adjacencies[i];

        for (size_t j = 0; j < graph->vertex_count; j++) {
            if (!node->next) {
                break;
            }

            Node *curr_node = node->next;

            while (curr_node->next) {
                if (strncmp(curr_node->vertex, curr_node->next->vertex, MAX_VERTEX_LABEL_LENGTH) > 0) {
                    Vertex temp;

                    strncpy(temp, curr_node->vertex, MAX_VERTEX_LABEL_LENGTH);
                    strncpy(curr_node->vertex, curr_node->next->vertex, MAX_VERTEX_LABEL_LENGTH);
                    strncpy(curr_node->next->vertex, temp, MAX_VERTEX_LABEL_LENGTH);
                }

                curr_node = curr_node->next;
            }
        }
    }
}
