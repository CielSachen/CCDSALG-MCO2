#include "social_network/graph.h"

#include <stdlib.h>
#include <string.h>

void create(Graph *const graph, const size_t vertex_cnt) {
    *(size_t *)&graph->vertex_count = vertex_cnt;
    graph->adjacencies_length = 0;

    for (size_t vertex_idx = 0; vertex_idx < MAX_GRAPH_VERTEX_COUNT; vertex_idx++) {
        for (size_t adjacency_idx = 0; adjacency_idx < MAX_GRAPH_VERTEX_COUNT; adjacency_idx++) {
            for (size_t i = 0; i < MAX_VERTEX_LABEL_LENGTH; i++) {
                graph->adjacencies_by_vertex[vertex_idx][adjacency_idx][i] = '\0';
            }
        }
    }
}

static size_t get_vertex_index(const Graph *const graph, const Vertex vertex) {
    for (size_t i = 0; i < graph->adjacencies_length; i++) {
        if (strncmp(graph->adjacencies_by_vertex[i][0], vertex, MAX_VERTEX_LABEL_LENGTH) == 0) {
            return i;
        }
    }

    return MAX_GRAPH_VERTEX_COUNT;
}

bool has_vertex(const Graph *const graph, const Vertex vertex) {
    return get_vertex_index(graph, vertex) != MAX_GRAPH_VERTEX_COUNT;
}

void add_edge(Graph *const graph, const Vertex src_vertex, const Vertex dest_vertex) {
    const bool has_src_vertex = has_vertex(graph, src_vertex);

    const size_t src_vertex_idx = has_src_vertex ? get_vertex_index(graph, src_vertex) : graph->adjacencies_length++;

    if (!has_src_vertex) {
        strncpy(graph->adjacencies_by_vertex[src_vertex_idx][0], src_vertex, MAX_VERTEX_LABEL_LENGTH);
    }

    if (!dest_vertex) {
        return;
    }

    size_t dest_vertex_idx = 1;

    while (strlen(graph->adjacencies_by_vertex[src_vertex_idx][dest_vertex_idx]) > 0) {
        dest_vertex_idx++;
    }

    strncpy(graph->adjacencies_by_vertex[src_vertex_idx][dest_vertex_idx], dest_vertex, MAX_VERTEX_LABEL_LENGTH);
}

static bool has_edge(const GraphEdge edges[], const size_t edge_cnt, const Vertex src_vertex,
                     const Vertex dest_vertex) {
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

void clone(const Graph *const graph, Graph *const new_graph) {
    create(new_graph, graph->vertex_count);

    for (size_t i = 0; i < new_graph->vertex_count; i++) {
        size_t j = 1;

        if (strlen(graph->adjacencies_by_vertex[i][j]) == 0) {
            add_edge(new_graph, graph->adjacencies_by_vertex[i][0], NULL);

            continue;
        }

        while (strlen(graph->adjacencies_by_vertex[i][j]) > 0) {
            add_edge(new_graph, graph->adjacencies_by_vertex[i][0], graph->adjacencies_by_vertex[i][j]);

            j++;
        }
    }
}

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

size_t get_adjacency_count(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT]) {
    size_t adjacency_cnt = 0;

    while (strlen(adjacencies_by_vertex[adjacency_cnt + 1]) > 0) {
        adjacency_cnt++;
    }

    return adjacency_cnt;
}

bool has_adjacency(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT], const Vertex vertex) {
    size_t adjacency_cnt = 1;

    while (strlen(adjacencies_by_vertex[adjacency_cnt]) > 0) {
        if (strncmp(adjacencies_by_vertex[adjacency_cnt], vertex, MAX_VERTEX_LABEL_LENGTH) == 0) {
            return true;
        }

        adjacency_cnt++;
    }

    return false;
}
