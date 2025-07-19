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

Graph *create_graph(const size_t vertex_count);

bool has_vertex(const Graph *const graph, const Vertex vertex);

bool add_edge(Graph *const graph, const Vertex source_vertex, const Vertex destination_vertex);

#endif  // SOCIAL_NETWORK_GRAPH_H_
