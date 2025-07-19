#include <stdio.h>
#include <string.h>

#include "social_network/io.h"

int main(void) {
    printf("TESTING PROGRAM!\n");

    // THIS WILL SIMPLY PRINT OUT THE CREATED ADJACENCY LIST TO VERIFY IF IT'S CORRECT

    char test_files[4][INPUT_BUFFER_SIZE] = {"../specs/input-files/A.txt", "../specs/input-files/G.txt",
                                             "../specs/input-files/Y.txt", "../specs/input-files/Z.txt"};

    for (size_t i = 0; i < 4; i++) {
        char *file_path = test_files[i];

        const Graph *const graph = parse_graph_from_file(file_path);

        if (!graph) {
            // The prior function already prints an error message.
            return 1;
        }

        printf("Graph %s", test_files[i]);
        printf("\n");
        printf("%ld\n", graph->vertex_count);

        for (size_t i = 0; i < graph->vertex_count; i++) {
            Node *curr_node = graph->adjacencies[i];

            printf("%s --> ", curr_node->vertex);

            while (curr_node->next) {
                curr_node = curr_node->next;

                printf("%s -- ", curr_node->vertex);
            }

            printf("-1\n");
        }

        if (i < 4) {
            printf("\n");
        }
    }

    return 0;
}
