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
        perror("Failed to Read the Input File");

        return NULL;
    }

    char in_buff[INPUT_BUFFER_SIZE];

    if (fgets(in_buff, sizeof in_buff, file) == NULL) {
        printf("The input file cannot be empty!\n");

        cleanup(file, NULL);

        return NULL;
    }

    //  Uses signed standard integer for compatibility with Windows. UGH!
    int vertex_cnt;

    sscanf(in_buff, "%d", &vertex_cnt);

    Graph *const graph = create_graph(vertex_cnt);

    if (!graph) {
        perror("Failed to allocate memory for a graph");

        cleanup(file, NULL);

        return NULL;
    }

    for (int i = 0; i < vertex_cnt; i++) {
        if (fgets(in_buff, sizeof in_buff, file) == NULL) {
            printf("The number of vertex labels is less than the number of vertices\n");

            cleanup(file, graph);

            return NULL;
        }

        char *adjacent_vertex_label = strtok(in_buff, WHITESPACE_DELIMITER);
        char vertex_label[MAX_VERTEX_LABEL_LENGTH];

        strncpy(vertex_label, adjacent_vertex_label, MAX_VERTEX_LABEL_LENGTH);

        adjacent_vertex_label = strtok(NULL, WHITESPACE_DELIMITER);

        while (adjacent_vertex_label != NULL) {
            if (strncmp(adjacent_vertex_label, NULL_VERTEX_LABEL, MAX_VERTEX_LABEL_LENGTH) == 0) {
                if (!has_vertex(graph, vertex_label) && !add_edge(graph, vertex_label, NULL)) {
                    perror("Failed to allocate memory for a linked list node");

                    cleanup(file, graph);

                    return NULL;
                }

                break;
            }

            if (!add_edge(graph, vertex_label, adjacent_vertex_label)) {
                perror("Failed to allocate memory for a linked list node");

                cleanup(file, graph);

                return NULL;
            }

            adjacent_vertex_label = strtok(NULL, WHITESPACE_DELIMITER);
        }
    }

    fclose(file);

    return graph;
}
