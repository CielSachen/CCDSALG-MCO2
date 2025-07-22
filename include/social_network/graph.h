#ifndef SOCIAL_NETWORK_GRAPH_H_
#define SOCIAL_NETWORK_GRAPH_H_

#include <stdbool.h>
#include <stddef.h>

#define MAX_VERTEX_LABEL_LENGTH 8

#define MAX_GRAPH_VERTEX_COUNT 20

typedef char Vertex[MAX_VERTEX_LABEL_LENGTH + 1];

typedef struct Graph {
    const size_t vertex_count;
    Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT][MAX_GRAPH_VERTEX_COUNT];
    size_t adjacencies_length;
} Graph;

typedef struct GraphEdge {
    Vertex source;
    Vertex destination;
} GraphEdge;

void create(Graph *const graph, const size_t vertex_count);

bool has_vertex(const Graph *const graph, const Vertex vertex);

void add_edge(Graph *const graph, const Vertex source_vertex, const Vertex destination_vertex);

void get_edges(const Graph *const graph, GraphEdge edges[], size_t *const edge_count);

void clone(const Graph *const graph, Graph *const new_graph);

void sort_adjacencies(Graph *const graph);

size_t get_adjacency_count(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT]);

bool has_adjacency(const Vertex adjacencies_by_vertex[MAX_GRAPH_VERTEX_COUNT], const Vertex vertex);

#endif  // SOCIAL_NETWORK_GRAPH_H_
