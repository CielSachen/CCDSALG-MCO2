#ifndef SOCIAL_NETWORK_GRAPH_H_
#define SOCIAL_NETWORK_GRAPH_H_

#include <stdbool.h>
#include <stddef.h>

#define MAX_VERTEX_LABEL_LENGTH 8

typedef char Vertex[MAX_VERTEX_LABEL_LENGTH + 1];

typedef struct Node {
    Vertex vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    const size_t vertex_count;
    Node **adjacencies;
    size_t adjacencies_length;
} Graph;

typedef struct GraphEdge {
    Vertex source;
    Vertex destination;
} GraphEdge;

Graph *create_graph(const size_t vertex_count);

bool has_vertex(const Graph *const graph, const Vertex vertex);

bool add_edge(Graph *const graph, const Vertex source_vertex, const Vertex destination_vertex);

GraphEdge **get_edges(const Graph *const graph);

Graph *clone_graph(const Graph *const graph);

void sort_graph_adjacencies(Graph *const graph);

#endif  // SOCIAL_NETWORK_GRAPH_H_
