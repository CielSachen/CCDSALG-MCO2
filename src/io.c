#include "social_network/io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void cleanup(FILE *file, Graph *graph) {
    if (graph) {
        free(graph);
    }

    if (file) {
        fclose(file);
    }
}

Graph *parse_graph_from_file(const char in_file_name[]) {
    FILE *file = fopen(in_file_name, "r");

    if (!file) {
        printf("File %s not found.", in_file_name);

        return NULL;
    }

    char in_buff[BUFFER_SIZE];

    // Presumption: Assume that the input file contents are correct.
    fgets(in_buff, sizeof in_buff, file);  // NOLINT

    int vertex_cnt;

    sscanf(in_buff, "%d", &vertex_cnt);

    Graph *const graph = create_graph(vertex_cnt);

    if (!graph) {
        cleanup(file, NULL);

        return NULL;
    }

    for (int i = 0; i < vertex_cnt; i++) {
        // Presumption: Assume that the input file contents are correct.
        fgets(in_buff, sizeof in_buff, file);  // NOLINT

        char *adjacent_vertex_label = strtok(in_buff, WHITESPACE_DELIMITER);
        Vertex vertex_label;

        strncpy(vertex_label, adjacent_vertex_label, MAX_VERTEX_LABEL_LENGTH);

        adjacent_vertex_label = strtok(NULL, WHITESPACE_DELIMITER);

        while (adjacent_vertex_label != NULL) {
            if (strncmp(adjacent_vertex_label, NULL_VERTEX_LABEL, MAX_VERTEX_LABEL_LENGTH) == 0) {
                if (!has_vertex(graph, vertex_label) && !add_edge(graph, vertex_label, NULL)) {
                    cleanup(file, graph);

                    return NULL;
                }

                break;
            }

            if (!add_edge(graph, vertex_label, adjacent_vertex_label)) {
                cleanup(file, graph);

                return NULL;
            }

            adjacent_vertex_label = strtok(NULL, WHITESPACE_DELIMITER);
        }
    }

    fclose(file);

    return graph;
}

void create_output_file_1(const Graph *const graph, const char graph_name) {
    char out_file_name[BUFFER_SIZE];

    sprintf(out_file_name, "%c-SET.txt", graph_name);

    FILE *out_file = fopen(out_file_name, "w");

    if (!out_file) {
        printf("File %s not created.", out_file_name);

        return;
    }

    fprintf(out_file, "V(%c)={", graph_name);

    for (size_t i = 0; i < graph->vertex_count; i++) {
        fprintf(out_file, "%s", graph->adjacencies[i]->vertex);

        if (i < graph->vertex_count - 1) {
            fprintf(out_file, ",");
        }
    }

    fprintf(out_file, "}\n");

    fprintf(out_file, "E(%c)={", graph_name);

    GraphEdge **graph_edges = get_edges(graph);

    for (size_t i = 0; graph_edges[i]; i++) {
        GraphEdge *graph_edge = graph_edges[i];

        fprintf(out_file, "(%s,%s)", graph_edge->source, graph_edge->destination);

        if (graph_edges[i + 1]) {
            fprintf(out_file, ",");
        }
    }

    fprintf(out_file, "}\n");

    fclose(out_file);
}
