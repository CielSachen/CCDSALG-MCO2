#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "social_network/io.h"

void print_graph(const Graph *const graph, const char graph_name) {
    printf("Graph %c", graph_name);
    printf("\n");
    printf("%ld\n", graph->vertex_count);

    for (size_t i = 0; i < graph->vertex_count; i++) {
        const Node *curr_node = graph->adjacencies[i];

        while (curr_node) {
            printf("%s->", curr_node->vertex);

            curr_node = curr_node->next;
        }

        printf("\\\n");
    }
}

int main(void) {
    printf("TESTING PROGRAM!\n");

    // THIS WILL SIMPLY PRINT OUT THE CREATED ADJACENCY LIST TO VERIFY IF IT'S CORRECT

    const char test_files[4][BUFFER_SIZE] = {"../specs/input-files/A.txt", "../specs/input-files/G.txt",
                                             "../specs/input-files/Y.txt", "../specs/input-files/Z.txt"};

    for (size_t i = 0; i < 4; i++) {
        const char *const file_path = test_files[i];

        Graph *const graph = parse_graph_from_file(file_path);

        if (!graph) {
            printf("The program ran out of memory.");

            return 1;
        }

        const char graph_name = test_files[i][21];

        print_graph(graph, graph_name);

        if (i < 4) {
            printf("\n");
        }

        Graph *const sorted_graph = clone_graph(graph);

        sort_graph_adjacencies(sorted_graph);

        create_output_file_1(sorted_graph, graph_name);

        free(sorted_graph);

        free(graph);
    }

    return 0;
}
